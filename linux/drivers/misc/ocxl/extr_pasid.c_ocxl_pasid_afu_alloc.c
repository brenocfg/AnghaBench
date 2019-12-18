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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int max_pasid_log; } ;
struct ocxl_fn {int /*<<< orphan*/  pasid_list; TYPE_1__ config; } ;

/* Variables and functions */
 int ENOSPC ; 
 int range_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 

int ocxl_pasid_afu_alloc(struct ocxl_fn *fn, u32 size)
{
	int max_pasid;

	if (fn->config.max_pasid_log < 0)
		return -ENOSPC;
	max_pasid = 1 << fn->config.max_pasid_log;
	return range_alloc(&fn->pasid_list, size, max_pasid, "afu pasid");
}