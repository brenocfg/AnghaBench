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
struct pm {int* data; scalar_t__ packetsize; scalar_t__ idx; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 scalar_t__ pm_checkpacket (int*) ; 

__attribute__((used)) static void pm_parse_6000(struct pm *pm)
{
	struct input_dev *dev = pm->dev;

	if ((pm->data[0] & 0xbf) == 0x30 && pm->packetsize == ++pm->idx) {
		if (pm_checkpacket(pm->data)) {
			input_report_abs(dev, ABS_X,
					pm->data[2] * 256 + pm->data[1]);
			input_report_abs(dev, ABS_Y,
					pm->data[4] * 256 + pm->data[3]);
			input_report_key(dev, BTN_TOUCH, pm->data[0] & 0x40);
			input_sync(dev);
		}
		pm->idx = 0;
	}
}