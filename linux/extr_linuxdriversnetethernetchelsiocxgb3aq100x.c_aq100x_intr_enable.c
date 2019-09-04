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
 int /*<<< orphan*/  AQ_IMASK_GLOBAL ; 
 int /*<<< orphan*/  AQ_IMASK_PMA ; 
 int /*<<< orphan*/  IMASK_GLOBAL ; 
 int /*<<< orphan*/  IMASK_PMA ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 int t3_mdio_write (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aq100x_intr_enable(struct cphy *phy)
{
	int err = t3_mdio_write(phy, MDIO_MMD_PMAPMD, AQ_IMASK_PMA, IMASK_PMA);
	if (err)
		return err;

	err = t3_mdio_write(phy, MDIO_MMD_VEND1, AQ_IMASK_GLOBAL, IMASK_GLOBAL);
	return err;
}