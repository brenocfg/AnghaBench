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
struct TYPE_2__ {struct bas_cardstate* bas; } ;
struct cardstate {TYPE_1__ hw; } ;
struct bas_cardstate {int /*<<< orphan*/  int_in_wq; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  timer_int_in; int /*<<< orphan*/  timer_cmd_in; int /*<<< orphan*/  timer_atrdy; int /*<<< orphan*/  timer_ctrl; struct cardstate* cs; int /*<<< orphan*/  lock; int /*<<< orphan*/  int_in_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IP_MSGSIZE ; 
 int /*<<< orphan*/  atrdy_timeout ; 
 int /*<<< orphan*/  cmd_in_timeout ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  int_in_resubmit ; 
 int /*<<< orphan*/  int_in_work ; 
 int /*<<< orphan*/  kfree (struct bas_cardstate*) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bas_cardstate* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  req_timeout ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gigaset_initcshw(struct cardstate *cs)
{
	struct bas_cardstate *ucs;

	cs->hw.bas = ucs = kzalloc(sizeof(*ucs), GFP_KERNEL);
	if (!ucs) {
		pr_err("out of memory\n");
		return -ENOMEM;
	}
	ucs->int_in_buf = kmalloc(IP_MSGSIZE, GFP_KERNEL);
	if (!ucs->int_in_buf) {
		kfree(ucs);
		pr_err("out of memory\n");
		return -ENOMEM;
	}

	spin_lock_init(&ucs->lock);
	ucs->cs = cs;
	timer_setup(&ucs->timer_ctrl, req_timeout, 0);
	timer_setup(&ucs->timer_atrdy, atrdy_timeout, 0);
	timer_setup(&ucs->timer_cmd_in, cmd_in_timeout, 0);
	timer_setup(&ucs->timer_int_in, int_in_resubmit, 0);
	init_waitqueue_head(&ucs->waitqueue);
	INIT_WORK(&ucs->int_in_wq, int_in_work);

	return 0;
}