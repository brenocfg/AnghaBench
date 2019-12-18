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
struct mvneta_port {int /*<<< orphan*/  comphy; int /*<<< orphan*/  phy_interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_MODE_ETHERNET ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 
 int phy_set_mode_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvneta_comphy_init(struct mvneta_port *pp)
{
	int ret;

	if (!pp->comphy)
		return 0;

	ret = phy_set_mode_ext(pp->comphy, PHY_MODE_ETHERNET,
			       pp->phy_interface);
	if (ret)
		return ret;

	return phy_power_on(pp->comphy);
}