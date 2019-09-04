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
struct file {struct binder_proc* private_data; } ;
struct binder_proc {int dummy; } ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_DEFERRED_FLUSH ; 
 int /*<<< orphan*/  binder_defer_work (struct binder_proc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int binder_flush(struct file *filp, fl_owner_t id)
{
	struct binder_proc *proc = filp->private_data;

	binder_defer_work(proc, BINDER_DEFERRED_FLUSH);

	return 0;
}