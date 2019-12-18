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
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 int __check_mem_type (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_vma (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_mem_type(unsigned long start, size_t num_pages)
{
	struct mm_struct *mm = current->mm;
	int rc;

	down_read(&mm->mmap_sem);
	rc = __check_mem_type(find_vma(mm, start),
			      start + num_pages * PAGE_SIZE);
	up_read(&mm->mmap_sem);

	return rc;
}