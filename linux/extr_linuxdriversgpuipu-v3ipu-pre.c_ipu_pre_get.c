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
typedef  int u32 ;
struct ipu_pre {int in_use; scalar_t__ regs; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IPU_PRE_CTRL ; 
 int IPU_PRE_CTRL_HANDSHAKE_ABORT_SKIP_EN ; 
 int IPU_PRE_CTRL_HANDSHAKE_EN ; 
 int IPU_PRE_CTRL_SDW_UPDATE ; 
 int IPU_PRE_CTRL_TPR_REST_SEL ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int ipu_pre_get(struct ipu_pre *pre)
{
	u32 val;

	if (pre->in_use)
		return -EBUSY;

	/* first get the engine out of reset and remove clock gating */
	writel(0, pre->regs + IPU_PRE_CTRL);

	/* init defaults that should be applied to all streams */
	val = IPU_PRE_CTRL_HANDSHAKE_ABORT_SKIP_EN |
	      IPU_PRE_CTRL_HANDSHAKE_EN |
	      IPU_PRE_CTRL_TPR_REST_SEL |
	      IPU_PRE_CTRL_SDW_UPDATE;
	writel(val, pre->regs + IPU_PRE_CTRL);

	pre->in_use = true;
	return 0;
}