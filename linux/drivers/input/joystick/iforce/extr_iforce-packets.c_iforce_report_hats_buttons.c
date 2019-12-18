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
typedef  int u8 ;
struct input_dev {int /*<<< orphan*/  absbit; } ;
struct iforce {TYPE_1__* type; struct input_dev* dev; } ;
struct TYPE_4__ {int x; int y; } ;
struct TYPE_3__ {scalar_t__* btn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_HAT0X ; 
 int /*<<< orphan*/  ABS_HAT0Y ; 
 int /*<<< orphan*/  ABS_HAT1X ; 
 int /*<<< orphan*/  ABS_HAT1Y ; 
 int BIT (int) ; 
 TYPE_2__* iforce_hat_to_axis ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,scalar_t__,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iforce_report_hats_buttons(struct iforce *iforce, u8 *data)
{
	struct input_dev *dev = iforce->dev;
	int i;

	input_report_abs(dev, ABS_HAT0X, iforce_hat_to_axis[data[6] >> 4].x);
	input_report_abs(dev, ABS_HAT0Y, iforce_hat_to_axis[data[6] >> 4].y);

	for (i = 0; iforce->type->btn[i] >= 0; i++)
		input_report_key(dev, iforce->type->btn[i],
				 data[(i >> 3) + 5] & (1 << (i & 7)));

	/* If there are untouched bits left, interpret them as the second hat */
	if (i <= 8) {
		u8 btns = data[6];

		if (test_bit(ABS_HAT1X, dev->absbit)) {
			if (btns & BIT(3))
				input_report_abs(dev, ABS_HAT1X, -1);
			else if (btns & BIT(1))
				input_report_abs(dev, ABS_HAT1X, 1);
			else
				input_report_abs(dev, ABS_HAT1X, 0);
		}

		if (test_bit(ABS_HAT1Y, dev->absbit)) {
			if (btns & BIT(0))
				input_report_abs(dev, ABS_HAT1Y, -1);
			else if (btns & BIT(2))
				input_report_abs(dev, ABS_HAT1Y, 1);
			else
				input_report_abs(dev, ABS_HAT1Y, 0);
		}
	}
}