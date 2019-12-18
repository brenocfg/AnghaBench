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
struct phylink_config {int dummy; } ;
struct phy_device {int dummy; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */

__attribute__((used)) static void axienet_mac_link_up(struct phylink_config *config,
				unsigned int mode,
				phy_interface_t interface,
				struct phy_device *phy)
{
	/* nothing meaningful to do */
}