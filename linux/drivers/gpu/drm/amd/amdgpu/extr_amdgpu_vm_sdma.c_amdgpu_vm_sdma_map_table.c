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
struct amdgpu_bo {TYPE_1__* shadow; int /*<<< orphan*/  tbo; } ;
struct TYPE_2__ {int /*<<< orphan*/  tbo; } ;

/* Variables and functions */
 int amdgpu_ttm_alloc_gart (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_vm_sdma_map_table(struct amdgpu_bo *table)
{
	int r;

	r = amdgpu_ttm_alloc_gart(&table->tbo);
	if (r)
		return r;

	if (table->shadow)
		r = amdgpu_ttm_alloc_gart(&table->shadow->tbo);

	return r;
}