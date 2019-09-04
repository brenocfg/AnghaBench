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
 int /*<<< orphan*/  DSAF_SUB_SC_NT_RESET_DREQ_REG ; 
 int /*<<< orphan*/  DSAF_SUB_SC_NT_RESET_REQ_REG ; 
 int /*<<< orphan*/  DSAF_SUB_SC_XBAR_RESET_DREQ_REG ; 
 int /*<<< orphan*/  DSAF_SUB_SC_XBAR_RESET_REQ_REG ; 
 int /*<<< orphan*/  RESET_REQ_OR_DREQ ; 
 int /*<<< orphan*/  dsaf_write_sub (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_dsaf_rst(struct dsaf_device *dsaf_dev, bool dereset)
{
	u32 xbar_reg_addr;
	u32 nt_reg_addr;

	if (!dereset) {
		xbar_reg_addr = DSAF_SUB_SC_XBAR_RESET_REQ_REG;
		nt_reg_addr = DSAF_SUB_SC_NT_RESET_REQ_REG;
	} else {
		xbar_reg_addr = DSAF_SUB_SC_XBAR_RESET_DREQ_REG;
		nt_reg_addr = DSAF_SUB_SC_NT_RESET_DREQ_REG;
	}

	dsaf_write_sub(dsaf_dev, xbar_reg_addr, RESET_REQ_OR_DREQ);
	dsaf_write_sub(dsaf_dev, nt_reg_addr, RESET_REQ_OR_DREQ);
}