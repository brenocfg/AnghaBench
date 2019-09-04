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
struct dss_pll {scalar_t__ base; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ PLL_STATUS ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int dss_wait_hsdiv_ack(struct dss_pll *pll, u32 hsdiv_ack_mask)
{
	int t = 100;

	while (t-- > 0) {
		u32 v = readl_relaxed(pll->base + PLL_STATUS);
		v &= hsdiv_ack_mask;
		if (v == hsdiv_ack_mask)
			return 0;
	}

	return -ETIMEDOUT;
}