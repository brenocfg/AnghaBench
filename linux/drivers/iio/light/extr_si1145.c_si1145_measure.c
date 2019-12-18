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
typedef  int /*<<< orphan*/  u8 ;
struct si1145_data {int /*<<< orphan*/  client; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; int /*<<< orphan*/  address; int /*<<< orphan*/  scan_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EOVERFLOW ; 
 scalar_t__ IIO_PROXIMITY ; 
 int /*<<< orphan*/  SI1145_CMD_ALS_FORCE ; 
 int /*<<< orphan*/  SI1145_CMD_PS_FORCE ; 
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct si1145_data* iio_priv (struct iio_dev*) ; 
 int si1145_command (struct si1145_data*,int /*<<< orphan*/ ) ; 
 int si1145_set_chlist (struct iio_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si1145_measure(struct iio_dev *indio_dev,
			  struct iio_chan_spec const *chan)
{
	struct si1145_data *data = iio_priv(indio_dev);
	u8 cmd;
	int ret;

	ret = si1145_set_chlist(indio_dev, BIT(chan->scan_index));
	if (ret < 0)
		return ret;

	cmd = (chan->type == IIO_PROXIMITY) ? SI1145_CMD_PS_FORCE :
		SI1145_CMD_ALS_FORCE;
	ret = si1145_command(data, cmd);
	if (ret < 0 && ret != -EOVERFLOW)
		return ret;

	return i2c_smbus_read_word_data(data->client, chan->address);
}