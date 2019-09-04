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
typedef  void* u32 ;
struct dsaf_tbl_tcam_mcast_cfg {void** tbl_mcast_port_msk; void* tbl_mcast_old_en; void* tbl_mcast_item_vld; } ;
struct dsaf_tbl_tcam_data {void* tbl_tcam_data_low; void* tbl_tcam_data_high; } ;
struct dsaf_device {int /*<<< orphan*/  tcam_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSAF_TBL_MCAST_CFG4_ITEM_VLD_S ; 
 int /*<<< orphan*/  DSAF_TBL_MCAST_CFG4_OLD_EN_S ; 
 int /*<<< orphan*/  DSAF_TBL_MCAST_CFG4_VM128_112_M ; 
 int /*<<< orphan*/  DSAF_TBL_MCAST_CFG4_VM128_112_S ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_RAM_RDATA0_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_RAM_RDATA1_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_RAM_RDATA2_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_RAM_RDATA3_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_RAM_RDATA4_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_RDATA_HIGH_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_RDATA_LOW_0_REG ; 
 void* dsaf_get_bit (void*,int /*<<< orphan*/ ) ; 
 void* dsaf_get_field (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* dsaf_read_dev (struct dsaf_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_dsaf_tbl_tcam_addr_cfg (struct dsaf_device*,void*) ; 
 int /*<<< orphan*/  hns_dsaf_tbl_tcam_load_pul (struct dsaf_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_dsaf_tcam_mc_get(
	struct dsaf_device *dsaf_dev, u32 address,
	struct dsaf_tbl_tcam_data *ptbl_tcam_data,
	struct dsaf_tbl_tcam_mcast_cfg *ptbl_tcam_mcast)
{
	u32 data_tmp;

	spin_lock_bh(&dsaf_dev->tcam_lock);

	/*Write Addr*/
	hns_dsaf_tbl_tcam_addr_cfg(dsaf_dev, address);

	/*read tcam item puls*/
	hns_dsaf_tbl_tcam_load_pul(dsaf_dev);

	/*read tcam data*/
	ptbl_tcam_data->tbl_tcam_data_high =
		dsaf_read_dev(dsaf_dev, DSAF_TBL_TCAM_RDATA_HIGH_0_REG);
	ptbl_tcam_data->tbl_tcam_data_low =
		dsaf_read_dev(dsaf_dev, DSAF_TBL_TCAM_RDATA_LOW_0_REG);

	/*read tcam mcast*/
	ptbl_tcam_mcast->tbl_mcast_port_msk[0] =
		dsaf_read_dev(dsaf_dev, DSAF_TBL_TCAM_RAM_RDATA0_0_REG);
	ptbl_tcam_mcast->tbl_mcast_port_msk[1] =
		dsaf_read_dev(dsaf_dev, DSAF_TBL_TCAM_RAM_RDATA1_0_REG);
	ptbl_tcam_mcast->tbl_mcast_port_msk[2] =
		dsaf_read_dev(dsaf_dev, DSAF_TBL_TCAM_RAM_RDATA2_0_REG);
	ptbl_tcam_mcast->tbl_mcast_port_msk[3] =
		dsaf_read_dev(dsaf_dev, DSAF_TBL_TCAM_RAM_RDATA3_0_REG);

	data_tmp = dsaf_read_dev(dsaf_dev, DSAF_TBL_TCAM_RAM_RDATA4_0_REG);
	ptbl_tcam_mcast->tbl_mcast_item_vld =
		dsaf_get_bit(data_tmp, DSAF_TBL_MCAST_CFG4_ITEM_VLD_S);
	ptbl_tcam_mcast->tbl_mcast_old_en =
		dsaf_get_bit(data_tmp, DSAF_TBL_MCAST_CFG4_OLD_EN_S);
	ptbl_tcam_mcast->tbl_mcast_port_msk[4] =
		dsaf_get_field(data_tmp, DSAF_TBL_MCAST_CFG4_VM128_112_M,
			       DSAF_TBL_MCAST_CFG4_VM128_112_S);

	spin_unlock_bh(&dsaf_dev->tcam_lock);
}