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
struct mdio_if_info {int mmds; int /*<<< orphan*/  prtad; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MDIO_AN_CTRL1_RESTART ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int MDIO_DEVS_AN ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  mdio_set_flag (struct mdio_if_info const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mdio45_nway_restart(const struct mdio_if_info *mdio)
{
	if (!(mdio->mmds & MDIO_DEVS_AN))
		return -EOPNOTSUPP;

	mdio_set_flag(mdio, mdio->prtad, MDIO_MMD_AN, MDIO_CTRL1,
		      MDIO_AN_CTRL1_RESTART, true);
	return 0;
}