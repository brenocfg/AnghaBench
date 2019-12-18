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
typedef  int u8 ;
struct bt455_regs {int addr_cmap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void bt455_write_cmap_next(struct bt455_regs *regs, u8 grey)
{
	wmb();
	regs->addr_cmap_data = 0x0;
	wmb();
	regs->addr_cmap_data = grey & 0xf;
	wmb();
	regs->addr_cmap_data = 0x0;
}