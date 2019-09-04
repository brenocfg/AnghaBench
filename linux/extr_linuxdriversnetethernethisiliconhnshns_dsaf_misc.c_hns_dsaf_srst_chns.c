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
 int /*<<< orphan*/  DSAF_SUB_SC_DSAF_RESET_DREQ_REG ; 
 int /*<<< orphan*/  DSAF_SUB_SC_DSAF_RESET_REQ_REG ; 
 int /*<<< orphan*/  dsaf_write_sub (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hns_dsaf_srst_chns(struct dsaf_device *dsaf_dev, u32 msk, bool dereset)
{
	u32 reg_addr;

	if (!dereset)
		reg_addr = DSAF_SUB_SC_DSAF_RESET_REQ_REG;
	else
		reg_addr = DSAF_SUB_SC_DSAF_RESET_DREQ_REG;

	dsaf_write_sub(dsaf_dev, reg_addr, msk);
}