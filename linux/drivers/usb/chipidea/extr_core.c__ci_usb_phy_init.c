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
struct ci_hdrc {int /*<<< orphan*/  usb_phy; scalar_t__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_exit (scalar_t__) ; 
 int phy_init (scalar_t__) ; 
 int phy_power_on (scalar_t__) ; 
 int usb_phy_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _ci_usb_phy_init(struct ci_hdrc *ci)
{
	int ret;

	if (ci->phy) {
		ret = phy_init(ci->phy);
		if (ret)
			return ret;

		ret = phy_power_on(ci->phy);
		if (ret) {
			phy_exit(ci->phy);
			return ret;
		}
	} else {
		ret = usb_phy_init(ci->usb_phy);
	}

	return ret;
}