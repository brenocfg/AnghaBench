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
struct ocxl_fn {int actag_base; } ;
struct ocxl_afu {int actag_base; int actag_enabled; struct ocxl_fn* fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocxl_actag_afu_free (struct ocxl_fn*,int,int) ; 

__attribute__((used)) static void reclaim_afu_actag(struct ocxl_afu *afu)
{
	struct ocxl_fn *fn = afu->fn;
	int start_offset, size;

	start_offset = afu->actag_base - fn->actag_base;
	size = afu->actag_enabled;
	ocxl_actag_afu_free(afu->fn, start_offset, size);
}