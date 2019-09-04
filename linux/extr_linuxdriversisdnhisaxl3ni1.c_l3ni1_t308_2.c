#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct l3_process {TYPE_2__* st; int /*<<< orphan*/  timer; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* l3l4 ) (TYPE_2__*,int /*<<< orphan*/ ,struct l3_process*) ;} ;
struct TYPE_4__ {TYPE_1__ l3; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_RELEASE_ERR ; 
 int /*<<< orphan*/  L3DelTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ni1_release_l3_process (struct l3_process*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,struct l3_process*) ; 

__attribute__((used)) static void
l3ni1_t308_2(struct l3_process *pc, u_char pr, void *arg)
{
	L3DelTimer(&pc->timer);
	pc->st->l3.l3l4(pc->st, CC_RELEASE_ERR, pc);
	ni1_release_l3_process(pc);
}