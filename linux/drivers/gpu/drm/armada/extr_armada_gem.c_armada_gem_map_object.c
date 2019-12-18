#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct armada_gem_object {void* addr; TYPE_1__ obj; int /*<<< orphan*/  phys_addr; scalar_t__ linear; } ;

/* Variables and functions */
 void* ioremap_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *
armada_gem_map_object(struct drm_device *dev, struct armada_gem_object *dobj)
{
	/* only linear objects need to be ioremap'd */
	if (!dobj->addr && dobj->linear)
		dobj->addr = ioremap_wc(dobj->phys_addr, dobj->obj.size);
	return dobj->addr;
}