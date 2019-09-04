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
typedef  int u64 ;
struct TYPE_2__ {int ack; int cmd; int tb; int /*<<< orphan*/  mark; scalar_t__ handshake; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  enter_contest (int /*<<< orphan*/ ,int) ; 
 int kExit ; 
 int kSetAndTest ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  running ; 
 int /*<<< orphan*/  set_tb (int,int) ; 
 TYPE_1__* tbsync ; 

void smp_generic_take_timebase(void)
{
	int cmd;
	u64 tb;
	unsigned long flags;

	local_irq_save(flags);
	while (!running)
		barrier();
	rmb();

	for (;;) {
		tbsync->ack = 1;
		while (!tbsync->handshake)
			barrier();
		rmb();

		cmd = tbsync->cmd;
		tb = tbsync->tb;
		mb();
		tbsync->ack = 0;
		if (cmd == kExit)
			break;

		while (tbsync->handshake)
			barrier();
		if (cmd == kSetAndTest)
			set_tb(tb >> 32, tb & 0xfffffffful);
		enter_contest(tbsync->mark, -1);
	}
	local_irq_restore(flags);
}