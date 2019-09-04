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
typedef  int u8 ;
struct sht15_data {scalar_t__ state; int val_status; int /*<<< orphan*/  dev; int /*<<< orphan*/  checksum_ok; scalar_t__ checksumming; int /*<<< orphan*/  data; int /*<<< orphan*/  wait_queue; int /*<<< orphan*/  read_work; int /*<<< orphan*/  interrupt_handled; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ETIME ; 
 scalar_t__ SHT15_READING_NOTHING ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int gpiod_direction_input (int /*<<< orphan*/ ) ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int sht15_connection_reset (struct sht15_data*) ; 
 int sht15_send_cmd (struct sht15_data*,int) ; 
 int sht15_send_status (struct sht15_data*,int) ; 
 int sht15_soft_reset (struct sht15_data*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sht15_measurement(struct sht15_data *data,
			     int command,
			     int timeout_msecs)
{
	int ret;
	u8 previous_config;

	ret = sht15_send_cmd(data, command);
	if (ret)
		return ret;

	ret = gpiod_direction_input(data->data);
	if (ret)
		return ret;
	atomic_set(&data->interrupt_handled, 0);

	enable_irq(gpiod_to_irq(data->data));
	if (gpiod_get_value(data->data) == 0) {
		disable_irq_nosync(gpiod_to_irq(data->data));
		/* Only relevant if the interrupt hasn't occurred. */
		if (!atomic_read(&data->interrupt_handled))
			schedule_work(&data->read_work);
	}
	ret = wait_event_timeout(data->wait_queue,
				 (data->state == SHT15_READING_NOTHING),
				 msecs_to_jiffies(timeout_msecs));
	if (data->state != SHT15_READING_NOTHING) { /* I/O error occurred */
		data->state = SHT15_READING_NOTHING;
		return -EIO;
	} else if (ret == 0) { /* timeout occurred */
		disable_irq_nosync(gpiod_to_irq(data->data));
		ret = sht15_connection_reset(data);
		if (ret)
			return ret;
		return -ETIME;
	}

	/*
	 *  Perform checksum validation on the received data.
	 *  Specification mentions that in case a checksum verification fails,
	 *  a soft reset command must be sent to the device.
	 */
	if (data->checksumming && !data->checksum_ok) {
		previous_config = data->val_status & 0x07;
		ret = sht15_soft_reset(data);
		if (ret)
			return ret;
		if (previous_config) {
			ret = sht15_send_status(data, previous_config);
			if (ret) {
				dev_err(data->dev,
					"CRC validation failed, unable "
					"to restore device settings\n");
				return ret;
			}
		}
		return -EAGAIN;
	}

	return 0;
}