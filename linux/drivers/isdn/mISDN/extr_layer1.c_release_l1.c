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
struct layer1 {TYPE_1__* dch; int /*<<< orphan*/  timer3; int /*<<< orphan*/  timerX; } ;
struct TYPE_2__ {int /*<<< orphan*/ * l1; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  kfree (struct layer1*) ; 
 int /*<<< orphan*/  mISDN_FsmDelTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
release_l1(struct layer1 *l1) {
	mISDN_FsmDelTimer(&l1->timerX, 0);
	mISDN_FsmDelTimer(&l1->timer3, 0);
	if (l1->dch)
		l1->dch->l1 = NULL;
	module_put(THIS_MODULE);
	kfree(l1);
}