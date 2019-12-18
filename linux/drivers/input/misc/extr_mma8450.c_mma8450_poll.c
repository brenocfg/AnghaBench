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
struct mma8450 {int dummy; } ;
struct input_polled_dev {int /*<<< orphan*/  input; struct mma8450* private; } ;
typedef  scalar_t__ s8 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  ABS_Z ; 
 int /*<<< orphan*/  MMA8450_OUT_X_LSB ; 
 int /*<<< orphan*/  MMA8450_STATUS ; 
 int MMA8450_STATUS_ZXYDR ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int mma8450_read (struct mma8450*,int /*<<< orphan*/ ) ; 
 int mma8450_read_block (struct mma8450*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void mma8450_poll(struct input_polled_dev *dev)
{
	struct mma8450 *m = dev->private;
	int x, y, z;
	int ret;
	u8 buf[6];

	ret = mma8450_read(m, MMA8450_STATUS);
	if (ret < 0)
		return;

	if (!(ret & MMA8450_STATUS_ZXYDR))
		return;

	ret = mma8450_read_block(m, MMA8450_OUT_X_LSB, buf, sizeof(buf));
	if (ret < 0)
		return;

	x = ((int)(s8)buf[1] << 4) | (buf[0] & 0xf);
	y = ((int)(s8)buf[3] << 4) | (buf[2] & 0xf);
	z = ((int)(s8)buf[5] << 4) | (buf[4] & 0xf);

	input_report_abs(dev->input, ABS_X, x);
	input_report_abs(dev->input, ABS_Y, y);
	input_report_abs(dev->input, ABS_Z, z);
	input_sync(dev->input);
}