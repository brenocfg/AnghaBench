#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_4__ {int cause; scalar_t__ loc; } ;
struct l3_process {int /*<<< orphan*/  timer; TYPE_3__* st; TYPE_1__ para; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* l3l4 ) (TYPE_3__*,int /*<<< orphan*/ ,struct l3_process*) ;} ;
struct TYPE_6__ {TYPE_2__ l3; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_RESUME_ERR ; 
 int /*<<< orphan*/  CC_T308_1 ; 
 int /*<<< orphan*/  L3AddTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L3DelTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MT_RELEASE ; 
 int /*<<< orphan*/  T308 ; 
 int /*<<< orphan*/  l3ni1_message (struct l3_process*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,struct l3_process*) ; 

__attribute__((used)) static void
l3ni1_t318(struct l3_process *pc, u_char pr, void *arg)
{
	L3DelTimer(&pc->timer);
	pc->para.cause = 102;	/* Timer expiry */
	pc->para.loc = 0;	/* local */
	pc->st->l3.l3l4(pc->st, CC_RESUME_ERR, pc);
	newl3state(pc, 19);
	l3ni1_message(pc, MT_RELEASE);
	L3AddTimer(&pc->timer, T308, CC_T308_1);
}