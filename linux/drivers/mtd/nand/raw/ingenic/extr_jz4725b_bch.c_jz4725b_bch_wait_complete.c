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
typedef  unsigned int u32 ;
struct ingenic_ecc {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ BCH_BHINT ; 
 int /*<<< orphan*/  BCH_TIMEOUT_US ; 
 int readl_relaxed_poll_timeout (scalar_t__,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int jz4725b_bch_wait_complete(struct ingenic_ecc *bch, unsigned int irq,
				     u32 *status)
{
	u32 reg;
	int ret;

	/*
	 * While we could use interrupts here and sleep until the operation
	 * completes, the controller works fairly quickly (usually a few
	 * microseconds) and so the overhead of sleeping until we get an
	 * interrupt quite noticeably decreases performance.
	 */
	ret = readl_relaxed_poll_timeout(bch->base + BCH_BHINT, reg,
					 reg & irq, 0, BCH_TIMEOUT_US);
	if (ret)
		return ret;

	if (status)
		*status = reg;

	writel(reg, bch->base + BCH_BHINT);

	return 0;
}