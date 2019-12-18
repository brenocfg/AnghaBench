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
typedef  int /*<<< orphan*/  u32 ;
struct dsaf_device {int /*<<< orphan*/  tcam_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSAF_TBL_TCAM_MCAST_CFG_0_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_MCAST_CFG_1_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_MCAST_CFG_2_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_MCAST_CFG_3_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_MCAST_CFG_4_0_REG ; 
 int /*<<< orphan*/  dsaf_write_dev (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_dsaf_tbl_tcam_addr_cfg (struct dsaf_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_dsaf_tbl_tcam_mcast_pul (struct dsaf_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_dsaf_tcam_mc_invld(struct dsaf_device *dsaf_dev, u32 address)
{
	spin_lock_bh(&dsaf_dev->tcam_lock);

	/*Write Addr*/
	hns_dsaf_tbl_tcam_addr_cfg(dsaf_dev, address);

	/*write tcam mcast*/
	dsaf_write_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_0_0_REG, 0);
	dsaf_write_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_1_0_REG, 0);
	dsaf_write_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_2_0_REG, 0);
	dsaf_write_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_3_0_REG, 0);
	dsaf_write_dev(dsaf_dev, DSAF_TBL_TCAM_MCAST_CFG_4_0_REG, 0);

	/*Write Plus*/
	hns_dsaf_tbl_tcam_mcast_pul(dsaf_dev);

	spin_unlock_bh(&dsaf_dev->tcam_lock);
}