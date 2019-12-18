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
struct msm_gpu {int dummy; } ;
struct a6xx_indexed_registers {int count; int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;
struct a6xx_gpu_state_obj {int /*<<< orphan*/ * data; void const* handle; } ;
struct a6xx_gpu_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpu_read (struct msm_gpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_write (struct msm_gpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * state_kcalloc (struct a6xx_gpu_state*,int,int) ; 

__attribute__((used)) static void a6xx_get_indexed_regs(struct msm_gpu *gpu,
		struct a6xx_gpu_state *a6xx_state,
		const struct a6xx_indexed_registers *indexed,
		struct a6xx_gpu_state_obj *obj)
{
	int i;

	obj->handle = (const void *) indexed;
	obj->data = state_kcalloc(a6xx_state, indexed->count, sizeof(u32));
	if (!obj->data)
		return;

	/* All the indexed banks start at address 0 */
	gpu_write(gpu, indexed->addr, 0);

	/* Read the data - each read increments the internal address by 1 */
	for (i = 0; i < indexed->count; i++)
		obj->data[i] = gpu_read(gpu, indexed->data);
}