#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ssp_sensor_data {int /*<<< orphan*/  (* process_data ) (struct iio_dev*,char*,int /*<<< orphan*/ ) ;} ;
struct ssp_data {int time_syncing; int /*<<< orphan*/  timestamp; struct iio_dev** sensor_devs; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  SSP_DEV ; 
#define  SSP_MSG2AP_INST_BIG_DATA 133 
#define  SSP_MSG2AP_INST_BYPASS_DATA 132 
#define  SSP_MSG2AP_INST_DEBUG_DATA 131 
#define  SSP_MSG2AP_INST_LIBRARY_DATA 130 
#define  SSP_MSG2AP_INST_RESET 129 
#define  SSP_MSG2AP_INST_TIME_SYNC 128 
 int SSP_SENSOR_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct ssp_sensor_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  ktime_get_real_ns () ; 
 int /*<<< orphan*/  ssp_handle_big_data (struct ssp_data*,char*,int*) ; 
 int* ssp_offset_map ; 
 int ssp_print_mcu_debug (char*,int*,int) ; 
 int /*<<< orphan*/  ssp_queue_ssp_refresh_task (struct ssp_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct iio_dev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ssp_parse_dataframe(struct ssp_data *data, char *dataframe, int len)
{
	int idx, sd;
	struct ssp_sensor_data *spd;
	struct iio_dev **indio_devs = data->sensor_devs;

	for (idx = 0; idx < len;) {
		switch (dataframe[idx++]) {
		case SSP_MSG2AP_INST_BYPASS_DATA:
			sd = dataframe[idx++];
			if (sd < 0 || sd >= SSP_SENSOR_MAX) {
				dev_err(SSP_DEV,
					"Mcu data frame1 error %d\n", sd);
				return -EPROTO;
			}

			if (indio_devs[sd]) {
				spd = iio_priv(indio_devs[sd]);
				if (spd->process_data)
					spd->process_data(indio_devs[sd],
							  &dataframe[idx],
							  data->timestamp);
			} else {
				dev_err(SSP_DEV, "no client for frame\n");
			}

			idx += ssp_offset_map[sd];
			break;
		case SSP_MSG2AP_INST_DEBUG_DATA:
			sd = ssp_print_mcu_debug(dataframe, &idx, len);
			if (sd) {
				dev_err(SSP_DEV,
					"Mcu data frame3 error %d\n", sd);
				return sd;
			}
			break;
		case SSP_MSG2AP_INST_LIBRARY_DATA:
			idx += len;
			break;
		case SSP_MSG2AP_INST_BIG_DATA:
			ssp_handle_big_data(data, dataframe, &idx);
			break;
		case SSP_MSG2AP_INST_TIME_SYNC:
			data->time_syncing = true;
			break;
		case SSP_MSG2AP_INST_RESET:
			ssp_queue_ssp_refresh_task(data, 0);
			break;
		}
	}

	if (data->time_syncing)
		data->timestamp = ktime_get_real_ns();

	return 0;
}