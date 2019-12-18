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
typedef  int /*<<< orphan*/  u32 ;
struct dwc3_omap {scalar_t__ utmi_otg_offset; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ USBOTGSS_UTMI_OTG_CTRL ; 
 int /*<<< orphan*/  dwc3_omap_writel (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dwc3_omap_write_utmi_ctrl(struct dwc3_omap *omap, u32 value)
{
	dwc3_omap_writel(omap->base, USBOTGSS_UTMI_OTG_CTRL +
					omap->utmi_otg_offset, value);

}