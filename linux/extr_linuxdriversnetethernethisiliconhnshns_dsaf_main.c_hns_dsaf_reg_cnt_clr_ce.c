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
 int /*<<< orphan*/  DSAF_CNT_CLR_CE_S ; 
 int /*<<< orphan*/  DSAF_DSA_REG_CNT_CLR_CE_REG ; 
 int /*<<< orphan*/  dsaf_set_dev_bit (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hns_dsaf_reg_cnt_clr_ce(struct dsaf_device *dsaf_dev, u32 reg_cnt_clr_ce)
{
	dsaf_set_dev_bit(dsaf_dev, DSAF_DSA_REG_CNT_CLR_CE_REG,
			 DSAF_CNT_CLR_CE_S, reg_cnt_clr_ce);
}