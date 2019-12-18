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
 size_t** con_region_offsets ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qed_memset_session_ctx(void *p_ctx_mem, u32 ctx_size, u8 ctx_type)
{
	u8 *x_val_ptr, *t_val_ptr, *u_val_ptr, *p_ctx;
	u8 x_val, t_val, u_val;

	p_ctx = (u8 * const)p_ctx_mem;
	x_val_ptr = &p_ctx[con_region_offsets[0][ctx_type]];
	t_val_ptr = &p_ctx[con_region_offsets[1][ctx_type]];
	u_val_ptr = &p_ctx[con_region_offsets[2][ctx_type]];

	x_val = *x_val_ptr;
	t_val = *t_val_ptr;
	u_val = *u_val_ptr;

	memset(p_ctx, 0, ctx_size);

	*x_val_ptr = x_val;
	*t_val_ptr = t_val;
	*u_val_ptr = u_val;
}