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
struct dsaf_tbl_line_cfg {int member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DSAF_LINE_SUM ; 
 int /*<<< orphan*/  hns_dsaf_single_line_tbl_cfg (struct dsaf_device*,scalar_t__,struct dsaf_tbl_line_cfg*) ; 

__attribute__((used)) static void hns_dsaf_tbl_line_init(struct dsaf_device *dsaf_dev)
{
	u32 i;
	/* defaultly set all lineal mac table entry resulting discard */
	struct dsaf_tbl_line_cfg tbl_line[] = {{1, 0, 0} };

	for (i = 0; i < DSAF_LINE_SUM; i++)
		hns_dsaf_single_line_tbl_cfg(dsaf_dev, i, tbl_line);
}