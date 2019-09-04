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
struct l3_process {int dummy; } ;
struct L3Timer {int /*<<< orphan*/  tl; struct l3_process* pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  L3ExpireTimer ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
L3InitTimer(struct l3_process *pc, struct L3Timer *t)
{
	t->pc = pc;
	timer_setup(&t->tl, L3ExpireTimer, 0);
}