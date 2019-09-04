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
 int /*<<< orphan*/  DSAF_TBL_LINE_ADDR_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_LINE_ADDR_M ; 
 int /*<<< orphan*/  DSAF_TBL_LINE_ADDR_S ; 
 int /*<<< orphan*/  dsaf_set_dev_field (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hns_dsaf_tbl_line_addr_cfg(struct dsaf_device *dsaf_dev,
					      u32 tab_line_addr)
{
	dsaf_set_dev_field(dsaf_dev, DSAF_TBL_LINE_ADDR_0_REG,
			   DSAF_TBL_LINE_ADDR_M, DSAF_TBL_LINE_ADDR_S,
			   tab_line_addr);
}