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
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSAF_SUB_SC_ROCEE_CLK_DIS_REG ; 
 int /*<<< orphan*/  DSAF_SUB_SC_ROCEE_CLK_EN_REG ; 
 int /*<<< orphan*/  DSAF_SUB_SC_ROCEE_RESET_DREQ_REG ; 
 int /*<<< orphan*/  DSAF_SUB_SC_ROCEE_RESET_REQ_REG ; 
 int /*<<< orphan*/  dsaf_write_sub (struct dsaf_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void hns_dsaf_roce_srst(struct dsaf_device *dsaf_dev, bool dereset)
{
	if (!dereset) {
		dsaf_write_sub(dsaf_dev, DSAF_SUB_SC_ROCEE_RESET_REQ_REG, 1);
	} else {
		dsaf_write_sub(dsaf_dev,
			       DSAF_SUB_SC_ROCEE_CLK_DIS_REG, 1);
		dsaf_write_sub(dsaf_dev,
			       DSAF_SUB_SC_ROCEE_RESET_DREQ_REG, 1);
		msleep(20);
		dsaf_write_sub(dsaf_dev, DSAF_SUB_SC_ROCEE_CLK_EN_REG, 1);
	}
}