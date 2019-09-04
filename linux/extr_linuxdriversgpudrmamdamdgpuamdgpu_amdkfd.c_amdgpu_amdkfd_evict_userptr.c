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
struct mm_struct {int dummy; } ;
struct kgd_mem {int dummy; } ;

/* Variables and functions */

int amdgpu_amdkfd_evict_userptr(struct kgd_mem *mem, struct mm_struct *mm)
{
	return 0;
}