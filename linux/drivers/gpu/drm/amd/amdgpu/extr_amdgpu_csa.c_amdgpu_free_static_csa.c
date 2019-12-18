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
 int /*<<< orphan*/  amdgpu_bo_free_kernel (struct amdgpu_bo**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void amdgpu_free_static_csa(struct amdgpu_bo **bo)
{
	amdgpu_bo_free_kernel(bo, NULL, NULL);
}