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
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSAF_TBL_DFX_BC_LKUP_NUM_EN_S ; 
 int /*<<< orphan*/  DSAF_TBL_DFX_CTRL_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_DFX_LINE_LKUP_NUM_EN_S ; 
 int /*<<< orphan*/  DSAF_TBL_DFX_MC_LKUP_NUM_EN_S ; 
 int /*<<< orphan*/  DSAF_TBL_DFX_UC_LKUP_NUM_EN_S ; 
 int /*<<< orphan*/  dsaf_read_dev (struct dsaf_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_dsaf_tbl_stat_en(struct dsaf_device *dsaf_dev)
{
	u32 o_tbl_ctrl;

	o_tbl_ctrl = dsaf_read_dev(dsaf_dev, DSAF_TBL_DFX_CTRL_0_REG);
	dsaf_set_bit(o_tbl_ctrl, DSAF_TBL_DFX_LINE_LKUP_NUM_EN_S, 1);
	dsaf_set_bit(o_tbl_ctrl, DSAF_TBL_DFX_UC_LKUP_NUM_EN_S, 1);
	dsaf_set_bit(o_tbl_ctrl, DSAF_TBL_DFX_MC_LKUP_NUM_EN_S, 1);
	dsaf_set_bit(o_tbl_ctrl, DSAF_TBL_DFX_BC_LKUP_NUM_EN_S, 1);
	dsaf_write_dev(dsaf_dev, DSAF_TBL_DFX_CTRL_0_REG, o_tbl_ctrl);
}