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
struct mm_struct {int /*<<< orphan*/  pinned_vm; } ;
struct TYPE_3__ {int /*<<< orphan*/  this_device; } ;
struct TYPE_4__ {TYPE_1__ mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 int ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 unsigned long atomic64_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 
 TYPE_2__ scif_info ; 
 int /*<<< orphan*/  scif_ulimit_check ; 

__attribute__((used)) static inline int __scif_check_inc_pinned_vm(struct mm_struct *mm,
					     int nr_pages)
{
	unsigned long locked, lock_limit;

	if (!mm || !nr_pages || !scif_ulimit_check)
		return 0;

	lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	locked = atomic64_add_return(nr_pages, &mm->pinned_vm);

	if ((locked > lock_limit) && !capable(CAP_IPC_LOCK)) {
		atomic64_sub(nr_pages, &mm->pinned_vm);
		dev_err(scif_info.mdev.this_device,
			"locked(%lu) > lock_limit(%lu)\n",
			locked, lock_limit);
		return -ENOMEM;
	}
	return 0;
}