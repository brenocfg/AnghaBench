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
struct dsaf_tbl_line_cfg {int /*<<< orphan*/  tbl_line_out_port; int /*<<< orphan*/  tbl_line_dvc; int /*<<< orphan*/  tbl_line_mac_discard; } ;
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSAF_TBL_LINE_CFG_DVC_S ; 
 int /*<<< orphan*/  DSAF_TBL_LINE_CFG_MAC_DISCARD_S ; 
 int /*<<< orphan*/  DSAF_TBL_LINE_CFG_OUT_PORT_M ; 
 int /*<<< orphan*/  DSAF_TBL_LINE_CFG_OUT_PORT_S ; 
 int /*<<< orphan*/  DSAF_TBL_LIN_CFG_0_REG ; 
 int /*<<< orphan*/  dsaf_read_dev (struct dsaf_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_dsaf_tbl_line_cfg(struct dsaf_device *dsaf_dev,
				  struct dsaf_tbl_line_cfg *tbl_lin)
{
	u32 tbl_line;

	tbl_line = dsaf_read_dev(dsaf_dev, DSAF_TBL_LIN_CFG_0_REG);
	dsaf_set_bit(tbl_line, DSAF_TBL_LINE_CFG_MAC_DISCARD_S,
		     tbl_lin->tbl_line_mac_discard);
	dsaf_set_bit(tbl_line, DSAF_TBL_LINE_CFG_DVC_S,
		     tbl_lin->tbl_line_dvc);
	dsaf_set_field(tbl_line, DSAF_TBL_LINE_CFG_OUT_PORT_M,
		       DSAF_TBL_LINE_CFG_OUT_PORT_S,
		       tbl_lin->tbl_line_out_port);
	dsaf_write_dev(dsaf_dev, DSAF_TBL_LIN_CFG_0_REG, tbl_line);
}