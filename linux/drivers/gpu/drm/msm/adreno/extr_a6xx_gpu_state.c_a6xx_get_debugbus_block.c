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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct msm_gpu {int dummy; } ;
struct a6xx_gpu_state_obj {int /*<<< orphan*/ * data; struct a6xx_debugbus_block const* handle; } ;
struct a6xx_gpu_state {int dummy; } ;
struct a6xx_debugbus_block {int count; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugbus_read (struct msm_gpu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * state_kcalloc (struct a6xx_gpu_state*,int,int) ; 

__attribute__((used)) static void a6xx_get_debugbus_block(struct msm_gpu *gpu,
		struct a6xx_gpu_state *a6xx_state,
		const struct a6xx_debugbus_block *block,
		struct a6xx_gpu_state_obj *obj)
{
	int i;
	u32 *ptr;

	obj->data = state_kcalloc(a6xx_state, block->count, sizeof(u64));
	if (!obj->data)
		return;

	obj->handle = block;

	for (ptr = obj->data, i = 0; i < block->count; i++)
		ptr += debugbus_read(gpu, block->id, i, ptr);
}