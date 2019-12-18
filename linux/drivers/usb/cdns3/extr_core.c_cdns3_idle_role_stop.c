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
struct cdns3 {int /*<<< orphan*/  usb3_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdns3_idle_role_stop(struct cdns3 *cdns)
{
	/* Program Lane swap and bring PHY out of RESET */
	phy_reset(cdns->usb3_phy);
}