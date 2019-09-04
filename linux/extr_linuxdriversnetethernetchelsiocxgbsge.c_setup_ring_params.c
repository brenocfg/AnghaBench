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
typedef  int u32 ;
struct adapter {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void setup_ring_params(struct adapter *adapter, u64 addr,
				     u32 size, int base_reg_lo,
				     int base_reg_hi, int size_reg)
{
	writel((u32)addr, adapter->regs + base_reg_lo);
	writel(addr >> 32, adapter->regs + base_reg_hi);
	writel(size, adapter->regs + size_reg);
}