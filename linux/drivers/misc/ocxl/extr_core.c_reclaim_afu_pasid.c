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
struct ocxl_fn {int pasid_base; } ;
struct TYPE_2__ {int pasid_supported_log; } ;
struct ocxl_afu {int pasid_base; struct ocxl_fn* fn; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocxl_pasid_afu_free (struct ocxl_fn*,int,int) ; 

__attribute__((used)) static void reclaim_afu_pasid(struct ocxl_afu *afu)
{
	struct ocxl_fn *fn = afu->fn;
	int start_offset, size;

	start_offset = afu->pasid_base - fn->pasid_base;
	size = 1 << afu->config.pasid_supported_log;
	ocxl_pasid_afu_free(afu->fn, start_offset, size);
}