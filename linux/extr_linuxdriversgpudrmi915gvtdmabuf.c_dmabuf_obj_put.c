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
struct intel_vgpu_dmabuf_obj {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmabuf_gem_object_free ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dmabuf_obj_put(struct intel_vgpu_dmabuf_obj *obj)
{
	kref_put(&obj->kref, dmabuf_gem_object_free);
}