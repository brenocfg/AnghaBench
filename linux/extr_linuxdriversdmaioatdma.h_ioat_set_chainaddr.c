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
typedef  int u64 ;
struct ioatdma_chan {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ IOAT2_CHAINADDR_OFFSET_HIGH ; 
 scalar_t__ IOAT2_CHAINADDR_OFFSET_LOW ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void
ioat_set_chainaddr(struct ioatdma_chan *ioat_chan, u64 addr)
{
	writel(addr & 0x00000000FFFFFFFF,
	       ioat_chan->reg_base + IOAT2_CHAINADDR_OFFSET_LOW);
	writel(addr >> 32,
	       ioat_chan->reg_base + IOAT2_CHAINADDR_OFFSET_HIGH);
}