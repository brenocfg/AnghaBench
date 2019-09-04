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
 int /*<<< orphan*/  AQ_IFLAG_GLOBAL ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 int cphy_cause_link_change ; 
 int t3_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int aq100x_intr_handler(struct cphy *phy)
{
	int err;
	unsigned int cause, v;

	err = t3_mdio_read(phy, MDIO_MMD_VEND1, AQ_IFLAG_GLOBAL, &cause);
	if (err)
		return err;

	/* Read (and reset) the latching version of the status */
	t3_mdio_read(phy, MDIO_MMD_PMAPMD, MDIO_STAT1, &v);

	return cphy_cause_link_change;
}