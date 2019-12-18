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
typedef  int /*<<< orphan*/  u16 ;
struct bt431_regs {int /*<<< orphan*/  addr_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt431_set_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline void bt431_write_reg_inc(struct bt431_regs *regs, u8 value)
{
	/*
	 * The compiler splits the write in two bytes without the
	 * helper variable.
	 */
	volatile u16 *r = &(regs->addr_reg);

	mb();
	*r = bt431_set_value(value);
}