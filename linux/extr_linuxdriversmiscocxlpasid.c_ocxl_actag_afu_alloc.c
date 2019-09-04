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
struct ocxl_fn {int actag_enabled; int /*<<< orphan*/  actag_list; } ;

/* Variables and functions */
 int range_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 

int ocxl_actag_afu_alloc(struct ocxl_fn *fn, u32 size)
{
	int max_actag;

	max_actag = fn->actag_enabled;
	return range_alloc(&fn->actag_list, size, max_actag, "afu actag");
}