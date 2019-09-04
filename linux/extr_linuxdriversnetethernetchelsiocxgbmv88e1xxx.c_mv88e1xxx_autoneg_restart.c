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
struct cphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_ANRESTART ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  mdio_set_bit (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e1xxx_autoneg_restart(struct cphy *cphy)
{
	mdio_set_bit(cphy, MII_BMCR, BMCR_ANRESTART);
	return 0;
}