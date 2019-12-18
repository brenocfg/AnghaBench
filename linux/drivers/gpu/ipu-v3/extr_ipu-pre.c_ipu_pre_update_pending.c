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
struct ipu_pre {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ IPU_PRE_CTRL ; 
 int IPU_PRE_CTRL_SDW_UPDATE ; 
 int readl_relaxed (scalar_t__) ; 

bool ipu_pre_update_pending(struct ipu_pre *pre)
{
	return !!(readl_relaxed(pre->regs + IPU_PRE_CTRL) &
		  IPU_PRE_CTRL_SDW_UPDATE);
}