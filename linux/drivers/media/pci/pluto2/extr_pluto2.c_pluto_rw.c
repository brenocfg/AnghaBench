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
typedef  size_t u32 ;
struct pluto {int /*<<< orphan*/ * io_mem; } ;

/* Variables and functions */
 size_t readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void pluto_rw(struct pluto *pluto, u32 reg, u32 mask, u32 bits)
{
	u32 val = readl(&pluto->io_mem[reg]);
	val &= ~mask;
	val |= bits;
	writel(val, &pluto->io_mem[reg]);
}