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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/ * br; } ;
struct binder_thread {TYPE_2__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/ * br; } ;
struct binder_proc {TYPE_1__ stats; } ;
struct TYPE_6__ {int /*<<< orphan*/ * br; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 size_t _IOC_NR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_3__ binder_stats ; 
 int /*<<< orphan*/  trace_binder_return (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void binder_stat_br(struct binder_proc *proc,
			   struct binder_thread *thread, uint32_t cmd)
{
	trace_binder_return(cmd);
	if (_IOC_NR(cmd) < ARRAY_SIZE(binder_stats.br)) {
		atomic_inc(&binder_stats.br[_IOC_NR(cmd)]);
		atomic_inc(&proc->stats.br[_IOC_NR(cmd)]);
		atomic_inc(&thread->stats.br[_IOC_NR(cmd)]);
	}
}