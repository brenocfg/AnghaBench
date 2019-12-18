#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_printer {int dummy; } ;
struct drm_gem_object {char* name; char* size; TYPE_3__* dev; TYPE_1__* funcs; scalar_t__ import_attach; int /*<<< orphan*/  vma_node; int /*<<< orphan*/  refcount; } ;
struct TYPE_6__ {TYPE_2__* driver; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* gem_print_info ) (struct drm_printer*,unsigned int,struct drm_gem_object const*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* print_info ) (struct drm_printer*,unsigned int,struct drm_gem_object const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_printf_indent (struct drm_printer*,unsigned int,char*,char*) ; 
 char* drm_vma_node_start (int /*<<< orphan*/ *) ; 
 char* kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_printer*,unsigned int,struct drm_gem_object const*) ; 
 int /*<<< orphan*/  stub2 (struct drm_printer*,unsigned int,struct drm_gem_object const*) ; 

void drm_gem_print_info(struct drm_printer *p, unsigned int indent,
			const struct drm_gem_object *obj)
{
	drm_printf_indent(p, indent, "name=%d\n", obj->name);
	drm_printf_indent(p, indent, "refcount=%u\n",
			  kref_read(&obj->refcount));
	drm_printf_indent(p, indent, "start=%08lx\n",
			  drm_vma_node_start(&obj->vma_node));
	drm_printf_indent(p, indent, "size=%zu\n", obj->size);
	drm_printf_indent(p, indent, "imported=%s\n",
			  obj->import_attach ? "yes" : "no");

	if (obj->funcs && obj->funcs->print_info)
		obj->funcs->print_info(p, indent, obj);
	else if (obj->dev->driver->gem_print_info)
		obj->dev->driver->gem_print_info(p, indent, obj);
}