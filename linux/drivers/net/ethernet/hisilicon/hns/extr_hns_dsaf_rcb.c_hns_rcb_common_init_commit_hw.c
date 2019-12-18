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
struct rcb_common_cb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCB_COM_CFG_SYS_FSH_REG ; 
 int /*<<< orphan*/  dsaf_write_dev (struct rcb_common_cb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmb () ; 

void hns_rcb_common_init_commit_hw(struct rcb_common_cb *rcb_common)
{
	wmb();	/* Sync point before breakpoint */
	dsaf_write_dev(rcb_common, RCB_COM_CFG_SYS_FSH_REG, 1);
	wmb();	/* Sync point after breakpoint */
}