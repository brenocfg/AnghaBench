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
struct reg_val {int member_0; int member_1; int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;
struct phy_device {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct reg_val const*) ; 
 int /*<<< orphan*/  MSCC_PHY_EXT_CNTL_STATUS ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_STANDARD ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_TEST ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_TR ; 
 int /*<<< orphan*/  MSCC_PHY_TEST_PAGE_24 ; 
 int /*<<< orphan*/  MSCC_PHY_TEST_PAGE_5 ; 
 int /*<<< orphan*/  MSCC_PHY_TEST_PAGE_8 ; 
 int SMI_BROADCAST_WR_EN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_modify_paged (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int phy_restore_page (struct phy_device*,int,int) ; 
 int phy_select_page (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsc85xx_tr_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vsc8531_pre_init_seq_set(struct phy_device *phydev)
{
	int rc;
	const struct reg_val init_seq[] = {
		{0x0f90, 0x00688980},
		{0x0696, 0x00000003},
		{0x07fa, 0x0050100f},
		{0x1686, 0x00000004},
	};
	unsigned int i;
	int oldpage;

	rc = phy_modify_paged(phydev, MSCC_PHY_PAGE_STANDARD,
			      MSCC_PHY_EXT_CNTL_STATUS, SMI_BROADCAST_WR_EN,
			      SMI_BROADCAST_WR_EN);
	if (rc < 0)
		return rc;
	rc = phy_modify_paged(phydev, MSCC_PHY_PAGE_TEST,
			      MSCC_PHY_TEST_PAGE_24, 0, 0x0400);
	if (rc < 0)
		return rc;
	rc = phy_modify_paged(phydev, MSCC_PHY_PAGE_TEST,
			      MSCC_PHY_TEST_PAGE_5, 0x0a00, 0x0e00);
	if (rc < 0)
		return rc;
	rc = phy_modify_paged(phydev, MSCC_PHY_PAGE_TEST,
			      MSCC_PHY_TEST_PAGE_8, 0x8000, 0x8000);
	if (rc < 0)
		return rc;

	mutex_lock(&phydev->lock);
	oldpage = phy_select_page(phydev, MSCC_PHY_PAGE_TR);
	if (oldpage < 0)
		goto out_unlock;

	for (i = 0; i < ARRAY_SIZE(init_seq); i++)
		vsc85xx_tr_write(phydev, init_seq[i].reg, init_seq[i].val);

out_unlock:
	oldpage = phy_restore_page(phydev, oldpage, oldpage);
	mutex_unlock(&phydev->lock);

	return oldpage;
}