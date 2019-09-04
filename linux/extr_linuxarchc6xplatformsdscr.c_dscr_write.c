#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct locked_reg {int /*<<< orphan*/  key; int /*<<< orphan*/  lockreg; } ;
struct TYPE_2__ {scalar_t__ base; scalar_t__* kick_key; int /*<<< orphan*/ * kick_reg; } ;

/* Variables and functions */
 TYPE_1__ dscr ; 
 int /*<<< orphan*/  dscr_write_locked1 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dscr_write_locked2 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 struct locked_reg* find_locked_reg (scalar_t__) ; 
 int /*<<< orphan*/  soc_writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void dscr_write(u32 reg, u32 val)
{
	struct locked_reg *lock;

	lock = find_locked_reg(reg);
	if (lock)
		dscr_write_locked1(reg, val, lock->lockreg, lock->key);
	else if (dscr.kick_key[0])
		dscr_write_locked2(reg, val, dscr.kick_reg[0], dscr.kick_key[0],
				   dscr.kick_reg[1], dscr.kick_key[1]);
	else
		soc_writel(val, dscr.base + reg);
}