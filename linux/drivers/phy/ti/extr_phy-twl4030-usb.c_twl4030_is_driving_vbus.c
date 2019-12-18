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
struct twl4030_usb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_CLK_CTRL_STS ; 
 int PHY_DPLL_CLK ; 
 int ULPI_OTG_CHRGVBUS ; 
 int /*<<< orphan*/  ULPI_OTG_CTRL ; 
 int ULPI_OTG_DRVVBUS ; 
 int twl4030_usb_read (struct twl4030_usb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool twl4030_is_driving_vbus(struct twl4030_usb *twl)
{
	int ret;

	ret = twl4030_usb_read(twl, PHY_CLK_CTRL_STS);
	if (ret < 0 || !(ret & PHY_DPLL_CLK))
		/*
		 * if clocks are off, registers are not updated,
		 * but we can assume we don't drive VBUS in this case
		 */
		return false;

	ret = twl4030_usb_read(twl, ULPI_OTG_CTRL);
	if (ret < 0)
		return false;

	return (ret & (ULPI_OTG_DRVVBUS | ULPI_OTG_CHRGVBUS)) ? true : false;
}