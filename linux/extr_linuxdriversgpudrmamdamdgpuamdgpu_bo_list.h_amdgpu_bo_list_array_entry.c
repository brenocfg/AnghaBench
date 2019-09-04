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
struct amdgpu_bo_list_entry {int dummy; } ;
struct amdgpu_bo_list {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct amdgpu_bo_list_entry *
amdgpu_bo_list_array_entry(struct amdgpu_bo_list *list, unsigned index)
{
	struct amdgpu_bo_list_entry *array = (void *)&list[1];

	return &array[index];
}