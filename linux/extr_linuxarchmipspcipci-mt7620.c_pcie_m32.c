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

/* Variables and functions */
 int /*<<< orphan*/  pcie_r32 (unsigned int) ; 
 int /*<<< orphan*/  pcie_w32 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void pcie_m32(u32 clr, u32 set, unsigned reg)
{
	u32 val = pcie_r32(reg);

	val &= ~clr;
	val |= set;
	pcie_w32(val, reg);
}