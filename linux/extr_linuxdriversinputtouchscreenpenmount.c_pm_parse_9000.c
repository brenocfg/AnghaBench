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

__attribute__((used)) static void pm_parse_9000(struct pm *pm)
{
	struct input_dev *dev = pm->dev;

	if ((pm->data[0] & 0x80) && pm->packetsize == ++pm->idx) {
		input_report_abs(dev, ABS_X, pm->data[1] * 128 + pm->data[2]);
		input_report_abs(dev, ABS_Y, pm->data[3] * 128 + pm->data[4]);
		input_report_key(dev, BTN_TOUCH, !!(pm->data[0] & 0x40));
		input_sync(dev);
		pm->idx = 0;
	}
}