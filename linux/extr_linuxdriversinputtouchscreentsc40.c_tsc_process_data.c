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
typedef  int u32 ;
struct tsc_ser {int* data; struct input_dev* dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void tsc_process_data(struct tsc_ser *ptsc)
{
	struct input_dev *dev = ptsc->dev;
	u8 *data = ptsc->data;
	u32 x;
	u32 y;

	x = ((data[1] & 0x03) << 8) | data[2];
	y = ((data[3] & 0x03) << 8) | data[4];

	input_report_abs(dev, ABS_X, x);
	input_report_abs(dev, ABS_Y, y);
	input_report_key(dev, BTN_TOUCH, 1);

	input_sync(dev);
}