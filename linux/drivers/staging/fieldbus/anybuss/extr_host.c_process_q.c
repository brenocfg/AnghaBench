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
typedef  int /*<<< orphan*/  t ;
struct kfifo {int dummy; } ;
struct anybuss_host {int dummy; } ;
struct ab_task {int /*<<< orphan*/  result; int /*<<< orphan*/  (* task_fn ) (struct anybuss_host*,struct ab_task*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  ab_task_dequeue_finish_put (struct kfifo*,struct anybuss_host*) ; 
 int kfifo_out_peek (struct kfifo*,struct ab_task**,int) ; 
 int /*<<< orphan*/  stub1 (struct anybuss_host*,struct ab_task*) ; 

__attribute__((used)) static void process_q(struct anybuss_host *cd, struct kfifo *q)
{
	struct ab_task *t;
	int ret;

	ret = kfifo_out_peek(q, &t, sizeof(t));
	if (!ret)
		return;
	t->result = t->task_fn(cd, t);
	if (t->result != -EINPROGRESS)
		ab_task_dequeue_finish_put(q, cd);
}