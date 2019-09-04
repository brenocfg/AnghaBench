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
struct gs_cb {int gsd; } ;
struct TYPE_3__ {struct gs_cb* gs_cb; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __ctl_set_bit (int,int) ; 
 TYPE_2__* current ; 
 struct gs_cb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_gs_cb (struct gs_cb*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static int gs_enable(void)
{
	struct gs_cb *gs_cb;

	if (!current->thread.gs_cb) {
		gs_cb = kzalloc(sizeof(*gs_cb), GFP_KERNEL);
		if (!gs_cb)
			return -ENOMEM;
		gs_cb->gsd = 25;
		preempt_disable();
		__ctl_set_bit(2, 4);
		load_gs_cb(gs_cb);
		current->thread.gs_cb = gs_cb;
		preempt_enable();
	}
	return 0;
}