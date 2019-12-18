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
struct ab_task {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __ab_task_finish (struct ab_task*,struct anybuss_host*) ; 
 int /*<<< orphan*/  ab_task_put (struct ab_task*) ; 
 int kfifo_out (struct kfifo*,struct ab_task**,int) ; 

__attribute__((used)) static void
ab_task_dequeue_finish_put(struct kfifo *q, struct anybuss_host *cd)
{
	int ret;
	struct ab_task *t;

	ret = kfifo_out(q, &t, sizeof(t));
	WARN_ON(!ret);
	__ab_task_finish(t, cd);
	ab_task_put(t);
}