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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AM35XX_CONTROL_DEVCONF2 ; 
 int /*<<< orphan*/  CONF2_FORCE_DEVICE ; 
 int /*<<< orphan*/  CONF2_FORCE_HOST ; 
 int /*<<< orphan*/  CONF2_NO_OVERRIDE ; 
 int /*<<< orphan*/  CONF2_OTGMODE ; 
#define  MUSB_HOST 130 
#define  MUSB_OTG 129 
#define  MUSB_PERIPHERAL 128 
 int /*<<< orphan*/  omap_ctrl_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_ctrl_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 

void am35x_set_mode(u8 musb_mode)
{
	u32 devconf2 = omap_ctrl_readl(AM35XX_CONTROL_DEVCONF2);

	devconf2 &= ~CONF2_OTGMODE;
	switch (musb_mode) {
	case MUSB_HOST:		/* Force VBUS valid, ID = 0 */
		devconf2 |= CONF2_FORCE_HOST;
		break;
	case MUSB_PERIPHERAL:	/* Force VBUS valid, ID = 1 */
		devconf2 |= CONF2_FORCE_DEVICE;
		break;
	case MUSB_OTG:		/* Don't override the VBUS/ID comparators */
		devconf2 |= CONF2_NO_OVERRIDE;
		break;
	default:
		pr_info("Unsupported mode %u\n", musb_mode);
	}

	omap_ctrl_writel(devconf2, AM35XX_CONTROL_DEVCONF2);
}