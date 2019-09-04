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
struct drm_device {TYPE_2__* dev_private; } ;
struct drm_buf {TYPE_3__* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  wrap; int /*<<< orphan*/  event; } ;
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* prev; TYPE_1__ age; } ;
struct TYPE_5__ {TYPE_3__ head; } ;
typedef  TYPE_2__ drm_savage_private_t ;
typedef  TYPE_3__ drm_savage_buf_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 

void savage_freelist_put(struct drm_device * dev, struct drm_buf * buf)
{
	drm_savage_private_t *dev_priv = dev->dev_private;
	drm_savage_buf_priv_t *entry = buf->dev_private, *prev, *next;

	DRM_DEBUG("age=0x%04x wrap=%d\n", entry->age.event, entry->age.wrap);

	if (entry->next != NULL || entry->prev != NULL) {
		DRM_ERROR("entry already on freelist.\n");
		return;
	}

	prev = &dev_priv->head;
	next = prev->next;
	prev->next = entry;
	next->prev = entry;
	entry->prev = prev;
	entry->next = next;
}