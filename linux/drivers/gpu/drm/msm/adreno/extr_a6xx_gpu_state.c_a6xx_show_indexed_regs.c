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
struct a6xx_indexed_registers {int count; int /*<<< orphan*/  name; } ;
struct a6xx_gpu_state_obj {int /*<<< orphan*/  data; struct a6xx_indexed_registers* handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,int) ; 
 int /*<<< orphan*/  print_ascii85 (struct drm_printer*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_name (struct drm_printer*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void a6xx_show_indexed_regs(struct a6xx_gpu_state_obj *obj,
		struct drm_printer *p)
{
	const struct a6xx_indexed_registers *indexed = obj->handle;

	if (!indexed)
		return;

	print_name(p, "  - regs-name: ", indexed->name);
	drm_printf(p, "    dwords: %d\n", indexed->count);

	print_ascii85(p, indexed->count << 2, obj->data);
}