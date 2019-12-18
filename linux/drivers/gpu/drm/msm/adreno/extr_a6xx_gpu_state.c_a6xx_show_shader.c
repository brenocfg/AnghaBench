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
struct drm_printer {int dummy; } ;
struct a6xx_shader_block {int size; int /*<<< orphan*/  name; } ;
struct a6xx_gpu_state_obj {scalar_t__ data; struct a6xx_shader_block* handle; } ;

/* Variables and functions */
 int A6XX_NUM_SHADER_BANKS ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,int) ; 
 int /*<<< orphan*/  print_ascii85 (struct drm_printer*,int,scalar_t__) ; 
 int /*<<< orphan*/  print_name (struct drm_printer*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a6xx_show_shader(struct a6xx_gpu_state_obj *obj,
		struct drm_printer *p)
{
	const struct a6xx_shader_block *block = obj->handle;
	int i;

	if (!obj->handle)
		return;

	print_name(p, "  - type: ", block->name);

	for (i = 0; i < A6XX_NUM_SHADER_BANKS; i++) {
		drm_printf(p, "    - bank: %d\n", i);
		drm_printf(p, "      size: %d\n", block->size);

		if (!obj->data)
			continue;

		print_ascii85(p, block->size << 2,
			obj->data + (block->size * i));
	}
}