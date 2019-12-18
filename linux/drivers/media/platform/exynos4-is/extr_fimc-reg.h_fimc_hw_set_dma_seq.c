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
struct fimc_dev {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ FIMC_REG_CIFCNTSEQ ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void fimc_hw_set_dma_seq(struct fimc_dev *dev, u32 mask)
{
	writel(mask, dev->regs + FIMC_REG_CIFCNTSEQ);
}