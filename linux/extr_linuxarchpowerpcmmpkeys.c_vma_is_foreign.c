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
struct vm_area_struct {scalar_t__ vm_mm; } ;
struct TYPE_2__ {scalar_t__ mm; } ;

/* Variables and functions */
 TYPE_1__* current ; 

__attribute__((used)) static inline bool vma_is_foreign(struct vm_area_struct *vma)
{
	if (!current->mm)
		return true;

	/* if it is not our ->mm, it has to be foreign */
	if (current->mm != vma->vm_mm)
		return true;

	return false;
}