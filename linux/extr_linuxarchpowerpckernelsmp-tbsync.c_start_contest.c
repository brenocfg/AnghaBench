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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int cmd; int handshake; scalar_t__ race_result; scalar_t__ ack; scalar_t__ mark; scalar_t__ tb; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  enter_contest (scalar_t__,int) ; 
 scalar_t__ get_tb () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 TYPE_1__* tbsync ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int start_contest(int cmd, long offset, int num)
{
	int i, score=0;
	u64 tb;
	u64 mark;

	tbsync->cmd = cmd;

	local_irq_disable();
	for (i = -3; i < num; ) {
		tb = get_tb() + 400;
		tbsync->tb = tb + offset;
		tbsync->mark = mark = tb + 400;

		wmb();

		tbsync->handshake = 1;
		while (tbsync->ack)
			barrier();

		while (get_tb() <= tb)
			barrier();
		tbsync->handshake = 0;
		enter_contest(mark, 1);

		while (!tbsync->ack)
			barrier();

		if (i++ > 0)
			score += tbsync->race_result;
	}
	local_irq_enable();
	return score;
}