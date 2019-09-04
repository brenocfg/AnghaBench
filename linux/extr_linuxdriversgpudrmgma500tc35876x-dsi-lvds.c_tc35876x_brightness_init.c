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
typedef  int u16 ;
struct drm_device {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOPWMCTRL ; 
 int /*<<< orphan*/  PWM0CLKDIV0 ; 
 int /*<<< orphan*/  PWM0CLKDIV1 ; 
 int /*<<< orphan*/  PWM_FREQUENCY ; 
 int /*<<< orphan*/  SYSTEMCLK ; 
 int calc_clkdiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int intel_scu_ipc_ioread8 (int /*<<< orphan*/ ,int*) ; 
 int intel_scu_ipc_iowrite8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tc35876x_brightness_init(struct drm_device *dev)
{
	int ret;
	u8 pwmctrl;
	u16 clkdiv;

	/* Make sure the PWM reference is the 19.2 MHz system clock. Read first
	 * instead of setting directly to catch potential conflicts between PWM
	 * users. */
	ret = intel_scu_ipc_ioread8(GPIOPWMCTRL, &pwmctrl);
	if (ret || pwmctrl != 0x01) {
		if (ret)
			dev_err(&dev->pdev->dev, "GPIOPWMCTRL read failed\n");
		else
			dev_warn(&dev->pdev->dev, "GPIOPWMCTRL was not set to system clock (pwmctrl = 0x%02x)\n", pwmctrl);

		ret = intel_scu_ipc_iowrite8(GPIOPWMCTRL, 0x01);
		if (ret)
			dev_err(&dev->pdev->dev, "GPIOPWMCTRL set failed\n");
	}

	clkdiv = calc_clkdiv(SYSTEMCLK, PWM_FREQUENCY);

	ret = intel_scu_ipc_iowrite8(PWM0CLKDIV1, (clkdiv >> 8) & 0xff);
	if (!ret)
		ret = intel_scu_ipc_iowrite8(PWM0CLKDIV0, clkdiv & 0xff);

	if (ret)
		dev_err(&dev->pdev->dev, "PWM0CLKDIV set failed\n");
	else
		dev_dbg(&dev->pdev->dev, "PWM0CLKDIV set to 0x%04x (%d Hz)\n",
			clkdiv, PWM_FREQUENCY);
}