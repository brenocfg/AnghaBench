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
struct mm_walk {struct mm_struct* mm; int /*<<< orphan*/  pte_entry; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_SIZE ; 
 int /*<<< orphan*/  __s390_reset_cmma ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  walk_page_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mm_walk*) ; 

void s390_reset_cmma(struct mm_struct *mm)
{
	struct mm_walk walk = { .pte_entry = __s390_reset_cmma };

	down_write(&mm->mmap_sem);
	walk.mm = mm;
	walk_page_range(0, TASK_SIZE, &walk);
	up_write(&mm->mmap_sem);
}