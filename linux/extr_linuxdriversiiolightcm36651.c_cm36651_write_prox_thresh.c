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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct cm36651_data {int* ps_ctrl_regs; int /*<<< orphan*/  ps_client; struct i2c_client* client; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 size_t CM36651_PS_THD ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,size_t,int) ; 
 struct cm36651_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int cm36651_write_prox_thresh(struct iio_dev *indio_dev,
					const struct iio_chan_spec *chan,
					enum iio_event_type type,
					enum iio_event_direction dir,
					enum iio_event_info info,
					int val, int val2)
{
	struct cm36651_data *cm36651 = iio_priv(indio_dev);
	struct i2c_client *client = cm36651->client;
	int ret;

	if (val < 3 || val > 255)
		return -EINVAL;

	cm36651->ps_ctrl_regs[CM36651_PS_THD] = val;
	ret = i2c_smbus_write_byte_data(cm36651->ps_client, CM36651_PS_THD,
					cm36651->ps_ctrl_regs[CM36651_PS_THD]);

	if (ret < 0) {
		dev_err(&client->dev, "PS threshold write failed: %d\n", ret);
		return ret;
	}

	return 0;
}