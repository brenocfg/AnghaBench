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
typedef  int u8 ;
struct phy_device {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDGE_RATE_CNTL_MASK ; 
 int EDGE_RATE_CNTL_POS ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_EXTENDED_2 ; 
 int /*<<< orphan*/  MSCC_PHY_WOL_MAC_CONTROL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_modify_paged (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vsc85xx_edge_rate_cntl_set(struct phy_device *phydev, u8 edge_rate)
{
	int rc;

	mutex_lock(&phydev->lock);
	rc = phy_modify_paged(phydev, MSCC_PHY_PAGE_EXTENDED_2,
			      MSCC_PHY_WOL_MAC_CONTROL, EDGE_RATE_CNTL_MASK,
			      edge_rate << EDGE_RATE_CNTL_POS);
	mutex_unlock(&phydev->lock);

	return rc;
}