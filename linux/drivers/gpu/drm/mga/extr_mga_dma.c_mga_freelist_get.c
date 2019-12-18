#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct drm_device {TYPE_3__* dev_private; } ;
struct drm_buf {int dummy; } ;
struct TYPE_9__ {TYPE_4__* tail; TYPE_2__* primary; TYPE_1__* sarea_priv; } ;
typedef  TYPE_3__ drm_mga_private_t ;
struct TYPE_11__ {int /*<<< orphan*/  wrap; scalar_t__ head; } ;
struct TYPE_10__ {struct drm_buf* buf; TYPE_5__ age; int /*<<< orphan*/ * next; struct TYPE_10__* prev; } ;
typedef  TYPE_4__ drm_mga_freelist_t ;
struct TYPE_8__ {scalar_t__ offset; } ;
struct TYPE_7__ {scalar_t__ last_wrap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  MGA_BUFFER_USED ; 
 int /*<<< orphan*/  MGA_PRIMADDRESS ; 
 scalar_t__ MGA_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_AGE (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_AGE (TYPE_5__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct drm_buf *mga_freelist_get(struct drm_device * dev)
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_freelist_t *next;
	drm_mga_freelist_t *prev;
	drm_mga_freelist_t *tail = dev_priv->tail;
	u32 head, wrap;
	DRM_DEBUG("\n");

	head = MGA_READ(MGA_PRIMADDRESS);
	wrap = dev_priv->sarea_priv->last_wrap;

	DRM_DEBUG("   tail=0x%06lx %d\n",
		  tail->age.head ?
		  (unsigned long)(tail->age.head - dev_priv->primary->offset) : 0,
		  tail->age.wrap);
	DRM_DEBUG("   head=0x%06lx %d\n",
		  (unsigned long)(head - dev_priv->primary->offset), wrap);

	if (TEST_AGE(&tail->age, head, wrap)) {
		prev = dev_priv->tail->prev;
		next = dev_priv->tail;
		prev->next = NULL;
		next->prev = next->next = NULL;
		dev_priv->tail = prev;
		SET_AGE(&next->age, MGA_BUFFER_USED, 0);
		return next->buf;
	}

	DRM_DEBUG("returning NULL!\n");
	return NULL;
}