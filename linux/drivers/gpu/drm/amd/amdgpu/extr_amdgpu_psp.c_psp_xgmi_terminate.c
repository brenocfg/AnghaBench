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
struct TYPE_2__ {int /*<<< orphan*/  xgmi_shared_buf; int /*<<< orphan*/  xgmi_shared_mc_addr; int /*<<< orphan*/  xgmi_shared_bo; scalar_t__ initialized; } ;
struct psp_context {TYPE_1__ xgmi_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int psp_xgmi_unload (struct psp_context*) ; 

__attribute__((used)) static int psp_xgmi_terminate(struct psp_context *psp)
{
	int ret;

	if (!psp->xgmi_context.initialized)
		return 0;

	ret = psp_xgmi_unload(psp);
	if (ret)
		return ret;

	psp->xgmi_context.initialized = 0;

	/* free xgmi shared memory */
	amdgpu_bo_free_kernel(&psp->xgmi_context.xgmi_shared_bo,
			&psp->xgmi_context.xgmi_shared_mc_addr,
			&psp->xgmi_context.xgmi_shared_buf);

	return 0;
}