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
struct anybuss_host {int dummy; } ;
struct ab_task {int /*<<< orphan*/  done; int /*<<< orphan*/  (* done_fn ) (struct anybuss_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct anybuss_host*) ; 

__attribute__((used)) static void __ab_task_finish(struct ab_task *t, struct anybuss_host *cd)
{
	if (t->done_fn)
		t->done_fn(cd);
	complete(&t->done);
}