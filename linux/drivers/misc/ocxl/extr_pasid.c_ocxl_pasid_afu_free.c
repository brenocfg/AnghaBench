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
typedef  int /*<<< orphan*/  u32 ;
struct ocxl_fn {int /*<<< orphan*/  pasid_list; } ;

/* Variables and functions */
 void range_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void ocxl_pasid_afu_free(struct ocxl_fn *fn, u32 start, u32 size)
{
	return range_free(&fn->pasid_list, start, size, "afu pasid");
}