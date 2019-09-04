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
struct TYPE_4__ {int cause; } ;
struct l3_process {TYPE_3__* st; TYPE_1__ para; int /*<<< orphan*/  timer; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* l3l4 ) (TYPE_3__*,int /*<<< orphan*/ ,struct l3_process*) ;} ;
struct TYPE_6__ {TYPE_2__ l3; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_CONNECT_ERR ; 
 int /*<<< orphan*/  L3DelTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l3_1tr6_disconnect_req (struct l3_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ,struct l3_process*) ; 

__attribute__((used)) static void
l3_1tr6_t313(struct l3_process *pc, u_char pr, void *arg)
{
	L3DelTimer(&pc->timer);
	pc->para.cause = 0xE6;
	l3_1tr6_disconnect_req(pc, pr, NULL);
	pc->st->l3.l3l4(pc->st, CC_CONNECT_ERR, pc);
}