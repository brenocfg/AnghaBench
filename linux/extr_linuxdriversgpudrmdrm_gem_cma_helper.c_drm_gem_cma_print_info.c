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
struct drm_gem_object {int dummy; } ;
struct drm_gem_cma_object {int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_printf_indent (struct drm_printer*,unsigned int,char*,int /*<<< orphan*/ *) ; 
 struct drm_gem_cma_object* to_drm_gem_cma_obj (struct drm_gem_object const*) ; 

void drm_gem_cma_print_info(struct drm_printer *p, unsigned int indent,
			    const struct drm_gem_object *obj)
{
	const struct drm_gem_cma_object *cma_obj = to_drm_gem_cma_obj(obj);

	drm_printf_indent(p, indent, "paddr=%pad\n", &cma_obj->paddr);
	drm_printf_indent(p, indent, "vaddr=%p\n", cma_obj->vaddr);
}