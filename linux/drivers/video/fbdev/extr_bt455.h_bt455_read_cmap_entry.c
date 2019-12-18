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
typedef  int /*<<< orphan*/  u8 ;
struct bt455_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt455_read_cmap_next (struct bt455_regs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt455_select_reg (struct bt455_regs*,int) ; 

__attribute__((used)) static inline void bt455_read_cmap_entry(struct bt455_regs *regs,
					 int cr, u8 *grey)
{
	bt455_select_reg(regs, cr);
	bt455_read_cmap_next(regs, grey);
}