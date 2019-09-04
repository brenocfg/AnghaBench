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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t** task_region_offsets ; 

void qed_memset_task_ctx(void *p_ctx_mem, u32 ctx_size, u8 ctx_type)
{
	u8 *p_ctx, *region1_val_ptr;
	u8 region1_val;

	p_ctx = (u8 * const)p_ctx_mem;
	region1_val_ptr = &p_ctx[task_region_offsets[0][ctx_type]];

	region1_val = *region1_val_ptr;

	memset(p_ctx, 0, ctx_size);

	*region1_val_ptr = region1_val;
}