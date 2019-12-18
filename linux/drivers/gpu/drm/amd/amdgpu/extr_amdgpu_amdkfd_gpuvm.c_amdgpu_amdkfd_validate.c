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
struct amdgpu_vm_parser {int /*<<< orphan*/  wait; int /*<<< orphan*/  domain; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int amdgpu_amdkfd_bo_validate (struct amdgpu_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_amdkfd_validate(void *param, struct amdgpu_bo *bo)
{
	struct amdgpu_vm_parser *p = param;

	return amdgpu_amdkfd_bo_validate(bo, p->domain, p->wait);
}