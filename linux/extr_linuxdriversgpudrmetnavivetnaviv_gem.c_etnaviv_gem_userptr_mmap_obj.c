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
struct vm_area_struct {int dummy; } ;
struct etnaviv_gem_object {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int etnaviv_gem_userptr_mmap_obj(struct etnaviv_gem_object *etnaviv_obj,
		struct vm_area_struct *vma)
{
	return -EINVAL;
}