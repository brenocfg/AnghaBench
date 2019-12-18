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
struct mm_struct {int /*<<< orphan*/  pinned_vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_ulimit_check ; 

__attribute__((used)) static inline int
__scif_dec_pinned_vm_lock(struct mm_struct *mm,
			  int nr_pages)
{
	if (!mm || !nr_pages || !scif_ulimit_check)
		return 0;

	atomic64_sub(nr_pages, &mm->pinned_vm);
	return 0;
}