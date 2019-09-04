#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/ * tail; TYPE_2__* head; } ;
typedef  TYPE_1__ drm_mga_private_t ;
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_2__ drm_mga_freelist_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 

__attribute__((used)) static void mga_freelist_cleanup(struct drm_device *dev)
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_freelist_t *entry;
	drm_mga_freelist_t *next;
	DRM_DEBUG("\n");

	entry = dev_priv->head;
	while (entry) {
		next = entry->next;
		kfree(entry);
		entry = next;
	}

	dev_priv->head = dev_priv->tail = NULL;
}