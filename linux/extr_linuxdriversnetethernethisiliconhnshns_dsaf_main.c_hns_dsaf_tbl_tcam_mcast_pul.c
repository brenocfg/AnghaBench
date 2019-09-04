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
 int /*<<< orphan*/  DSAF_TBL_PUL_0_REG ; 
 int /*<<< orphan*/  DSAF_TBL_PUL_MCAST_VLD_S ; 
 int /*<<< orphan*/  dsaf_read_dev (struct dsaf_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsaf_write_dev (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_dsaf_tbl_tcam_mcast_pul(struct dsaf_device *dsaf_dev)
{
	u32 o_tbl_pul;

	o_tbl_pul = dsaf_read_dev(dsaf_dev, DSAF_TBL_PUL_0_REG);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_MCAST_VLD_S, 1);
	dsaf_write_dev(dsaf_dev, DSAF_TBL_PUL_0_REG, o_tbl_pul);
	dsaf_set_bit(o_tbl_pul, DSAF_TBL_PUL_MCAST_VLD_S, 0);
	dsaf_write_dev(dsaf_dev, DSAF_TBL_PUL_0_REG, o_tbl_pul);
}