#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct st_sensor_data {int /*<<< orphan*/  multiread_bit; int /*<<< orphan*/  dev; int /*<<< orphan*/  tb; TYPE_2__* tf; } ;
struct iio_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ shift; scalar_t__ realbits; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; TYPE_1__ scan_type; } ;
typedef  int s8 ;
typedef  int s32 ;
typedef  int s16 ;
struct TYPE_4__ {int (* read_multiple_byte ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,scalar_t__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (scalar_t__,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ get_unaligned_le16 (scalar_t__*) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ st_sensors_get_unaligned_le24 (scalar_t__*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_sensors_read_axis_data(struct iio_dev *indio_dev,
				struct iio_chan_spec const *ch, int *data)
{
	int err;
	u8 *outdata;
	struct st_sensor_data *sdata = iio_priv(indio_dev);
	unsigned int byte_for_channel;

	byte_for_channel = DIV_ROUND_UP(ch->scan_type.realbits +
					ch->scan_type.shift, 8);
	outdata = kmalloc(byte_for_channel, GFP_KERNEL);
	if (!outdata)
		return -ENOMEM;

	err = sdata->tf->read_multiple_byte(&sdata->tb, sdata->dev,
				ch->address, byte_for_channel,
				outdata, sdata->multiread_bit);
	if (err < 0)
		goto st_sensors_free_memory;

	if (byte_for_channel == 1)
		*data = (s8)*outdata;
	else if (byte_for_channel == 2)
		*data = (s16)get_unaligned_le16(outdata);
	else if (byte_for_channel == 3)
		*data = (s32)st_sensors_get_unaligned_le24(outdata);

st_sensors_free_memory:
	kfree(outdata);

	return err;
}