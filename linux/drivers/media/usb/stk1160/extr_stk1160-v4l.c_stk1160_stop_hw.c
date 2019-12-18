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
struct stk1160 {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  udev; scalar_t__ alt; } ;

/* Variables and functions */
 scalar_t__ STK1160_DCTRL ; 
 int /*<<< orphan*/  s_stream ; 
 int /*<<< orphan*/  stk1160_dbg (char*,scalar_t__) ; 
 int /*<<< orphan*/  stk1160_write_reg (struct stk1160*,scalar_t__,int) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static void stk1160_stop_hw(struct stk1160 *dev)
{
	/* If the device is not physically present, there is nothing to do */
	if (!dev->udev)
		return;

	/* set alternate 0 */
	dev->alt = 0;
	stk1160_dbg("setting alternate %d\n", dev->alt);
	usb_set_interface(dev->udev, 0, 0);

	/* Stop stk1160 */
	stk1160_write_reg(dev, STK1160_DCTRL, 0x00);
	stk1160_write_reg(dev, STK1160_DCTRL+3, 0x00);

	/* Stop saa711x */
	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_stream, 0);
}