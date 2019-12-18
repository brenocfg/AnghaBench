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
struct task_struct {int dummy; } ;
struct closure_syncer {int done; int /*<<< orphan*/  task; } ;
struct closure {struct closure_syncer* s; } ;

/* Variables and functions */
 struct task_struct* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static void closure_sync_fn(struct closure *cl)
{
	struct closure_syncer *s = cl->s;
	struct task_struct *p;

	rcu_read_lock();
	p = READ_ONCE(s->task);
	s->done = 1;
	wake_up_process(p);
	rcu_read_unlock();
}