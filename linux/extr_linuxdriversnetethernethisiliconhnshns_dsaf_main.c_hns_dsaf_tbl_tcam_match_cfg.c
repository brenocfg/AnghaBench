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
struct dsaf_tbl_tcam_data {int /*<<< orphan*/  tbl_tcam_data_high; int /*<<< orphan*/  tbl_tcam_data_low; } ;
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSAF_TBL_TCAM_MATCH_CFG_H_REG ; 
 int /*<<< orphan*/  DSAF_TBL_TCAM_MATCH_CFG_L_REG ; 
 int /*<<< orphan*/  dsaf_write_dev (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_dsaf_tbl_tcam_match_cfg(
	struct dsaf_device *dsaf_dev,
	struct dsaf_tbl_tcam_data *ptbl_tcam_data)
{
	dsaf_write_dev(dsaf_dev, DSAF_TBL_TCAM_MATCH_CFG_L_REG,
		       ptbl_tcam_data->tbl_tcam_data_low);
	dsaf_write_dev(dsaf_dev, DSAF_TBL_TCAM_MATCH_CFG_H_REG,
		       ptbl_tcam_data->tbl_tcam_data_high);
}