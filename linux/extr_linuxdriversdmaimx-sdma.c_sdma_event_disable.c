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
typedef  scalar_t__ u32 ;
struct sdma_engine {scalar_t__ regs; } ;
struct sdma_channel {int channel; struct sdma_engine* sdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int,unsigned long*) ; 
 scalar_t__ chnenbl_ofs (struct sdma_engine*,unsigned int) ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static void sdma_event_disable(struct sdma_channel *sdmac, unsigned int event)
{
	struct sdma_engine *sdma = sdmac->sdma;
	int channel = sdmac->channel;
	u32 chnenbl = chnenbl_ofs(sdma, event);
	unsigned long val;

	val = readl_relaxed(sdma->regs + chnenbl);
	__clear_bit(channel, &val);
	writel_relaxed(val, sdma->regs + chnenbl);
}