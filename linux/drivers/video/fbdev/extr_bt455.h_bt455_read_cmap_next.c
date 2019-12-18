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
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  rmb () ; 

__attribute__((used)) static inline void bt455_read_cmap_next(struct bt455_regs *regs, u8 *grey)
{
	mb();
	regs->addr_cmap_data;
	rmb();
	*grey = regs->addr_cmap_data & 0xf;
	rmb();
	regs->addr_cmap_data;
}