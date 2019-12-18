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
struct ufs_err_reg_hist {size_t pos; int /*<<< orphan*/ * tstamp; int /*<<< orphan*/ * reg; } ;

/* Variables and functions */
 int UFS_ERR_REG_HIST_LENGTH ; 
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static void ufshcd_update_reg_hist(struct ufs_err_reg_hist *reg_hist,
				   u32 reg)
{
	reg_hist->reg[reg_hist->pos] = reg;
	reg_hist->tstamp[reg_hist->pos] = ktime_get();
	reg_hist->pos = (reg_hist->pos + 1) % UFS_ERR_REG_HIST_LENGTH;
}