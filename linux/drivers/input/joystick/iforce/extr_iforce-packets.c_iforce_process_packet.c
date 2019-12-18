#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct input_dev {int /*<<< orphan*/  absbit; } ;
struct iforce {TYPE_1__* core_effects; struct input_dev* dev; } ;
typedef  int /*<<< orphan*/  __s8 ;
typedef  int /*<<< orphan*/  __s16 ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_BRAKE ; 
 int /*<<< orphan*/  ABS_GAS ; 
 int /*<<< orphan*/  ABS_RUDDER ; 
 int /*<<< orphan*/  ABS_THROTTLE ; 
 int /*<<< orphan*/  ABS_WHEEL ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_DEAD ; 
 int /*<<< orphan*/  FF_CORE_IS_PLAYED ; 
 int /*<<< orphan*/  FF_STATUS_PLAYING ; 
 int /*<<< orphan*/  FF_STATUS_STOPPED ; 
 int /*<<< orphan*/  get_unaligned_le16 (int*) ; 
 int /*<<< orphan*/  iforce_report_hats_buttons (struct iforce*,int*) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_ff_status (struct input_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  mark_core_as_ready (struct iforce*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void iforce_process_packet(struct iforce *iforce,
			   u8 packet_id, u8 *data, size_t len)
{
	struct input_dev *dev = iforce->dev;
	int i, j;

	switch (packet_id) {

	case 0x01:	/* joystick position data */
		input_report_abs(dev, ABS_X,
				 (__s16) get_unaligned_le16(data));
		input_report_abs(dev, ABS_Y,
				 (__s16) get_unaligned_le16(data + 2));
		input_report_abs(dev, ABS_THROTTLE, 255 - data[4]);

		if (len >= 8 && test_bit(ABS_RUDDER ,dev->absbit))
			input_report_abs(dev, ABS_RUDDER, (__s8)data[7]);

		iforce_report_hats_buttons(iforce, data);

		input_sync(dev);
		break;

	case 0x03:	/* wheel position data */
		input_report_abs(dev, ABS_WHEEL,
				 (__s16) get_unaligned_le16(data));
		input_report_abs(dev, ABS_GAS,   255 - data[2]);
		input_report_abs(dev, ABS_BRAKE, 255 - data[3]);

		iforce_report_hats_buttons(iforce, data);

		input_sync(dev);
		break;

	case 0x02:	/* status report */
		input_report_key(dev, BTN_DEAD, data[0] & 0x02);
		input_sync(dev);

		/* Check if an effect was just started or stopped */
		i = data[1] & 0x7f;
		if (data[1] & 0x80) {
			if (!test_and_set_bit(FF_CORE_IS_PLAYED, iforce->core_effects[i].flags)) {
				/* Report play event */
				input_report_ff_status(dev, i, FF_STATUS_PLAYING);
			}
		} else if (test_and_clear_bit(FF_CORE_IS_PLAYED, iforce->core_effects[i].flags)) {
			/* Report stop event */
			input_report_ff_status(dev, i, FF_STATUS_STOPPED);
		}

		for (j = 3; j < len; j += 2)
			mark_core_as_ready(iforce, get_unaligned_le16(data + j));

		break;
	}
}