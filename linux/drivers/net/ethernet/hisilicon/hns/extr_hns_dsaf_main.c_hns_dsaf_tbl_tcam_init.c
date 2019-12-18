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
typedef  scalar_t__ u32 ;
struct dsaf_tbl_tcam_ucast_cfg {int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dsaf_tbl_tcam_data {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DSAF_TCAM_SUM ; 
 int /*<<< orphan*/  hns_dsaf_tcam_uc_cfg (struct dsaf_device*,scalar_t__,struct dsaf_tbl_tcam_data*,struct dsaf_tbl_tcam_ucast_cfg*) ; 

__attribute__((used)) static void hns_dsaf_tbl_tcam_init(struct dsaf_device *dsaf_dev)
{
	u32 i;
	struct dsaf_tbl_tcam_data tcam_data[] = {{0, 0} };
	struct dsaf_tbl_tcam_ucast_cfg tcam_ucast[] = {{0, 0, 0, 0, 0} };

	/*tcam tbl*/
	for (i = 0; i < DSAF_TCAM_SUM; i++)
		hns_dsaf_tcam_uc_cfg(dsaf_dev, i, tcam_data, tcam_ucast);
}