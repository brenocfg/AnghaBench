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
struct TYPE_3__ {int /*<<< orphan*/  bd_addr; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; TYPE_1__ context; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MPX_INVALID_BOUNDS_DIR ; 
 int /*<<< orphan*/  X86_FEATURE_MPX ; 
 int /*<<< orphan*/  cpu_feature_enabled (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int mpx_disable_management(void)
{
	struct mm_struct *mm = current->mm;

	if (!cpu_feature_enabled(X86_FEATURE_MPX))
		return -ENXIO;

	down_write(&mm->mmap_sem);
	mm->context.bd_addr = MPX_INVALID_BOUNDS_DIR;
	up_write(&mm->mmap_sem);
	return 0;
}