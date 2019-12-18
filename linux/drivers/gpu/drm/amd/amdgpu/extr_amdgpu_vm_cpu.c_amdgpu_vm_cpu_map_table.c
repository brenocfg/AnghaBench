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
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int amdgpu_bo_kmap (struct amdgpu_bo*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_vm_cpu_map_table(struct amdgpu_bo *table)
{
	return amdgpu_bo_kmap(table, NULL);
}