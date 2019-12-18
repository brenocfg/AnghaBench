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
typedef  int u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PHYCTRL_DR_100OHM ; 
 int PHYCTRL_DR_33OHM ; 
 int PHYCTRL_DR_40OHM ; 
 int PHYCTRL_DR_50OHM ; 
 int PHYCTRL_DR_66OHM ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static u32 convert_drive_impedance_ohm(struct platform_device *pdev, u32 dr_ohm)
{
	switch (dr_ohm) {
	case 100:
		return PHYCTRL_DR_100OHM;
	case 66:
		return PHYCTRL_DR_66OHM;
	case 50:
		return PHYCTRL_DR_50OHM;
	case 40:
		return PHYCTRL_DR_40OHM;
	case 33:
		return PHYCTRL_DR_33OHM;
	}

	dev_warn(&pdev->dev, "Invalid value %u for drive-impedance-ohm.\n",
		 dr_ohm);
	return PHYCTRL_DR_50OHM;
}