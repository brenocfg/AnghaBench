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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {scalar_t__ cause; } ;
struct l3_process {scalar_t__ N303; TYPE_1__ para; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  L3DelTimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l3_1tr6_disconnect_req (struct l3_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l3_1tr6_setup_req (struct l3_process*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
l3_1tr6_t303(struct l3_process *pc, u_char pr, void *arg)
{
	if (pc->N303 > 0) {
		pc->N303--;
		L3DelTimer(&pc->timer);
		l3_1tr6_setup_req(pc, pr, arg);
	} else {
		L3DelTimer(&pc->timer);
		pc->para.cause = 0;
		l3_1tr6_disconnect_req(pc, 0, NULL);
	}
}