#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct drm_device {TYPE_2__* dev_private; } ;
struct drm_buf {int dummy; } ;
struct TYPE_5__ {TYPE_3__* prev; } ;
struct TYPE_6__ {int* status_ptr; unsigned int event_wrap; int event_counter; TYPE_1__ tail; } ;
typedef  TYPE_2__ drm_savage_private_t ;
struct TYPE_8__ {int /*<<< orphan*/  wrap; int /*<<< orphan*/  event; } ;
struct TYPE_7__ {struct drm_buf* buf; struct TYPE_7__* prev; struct TYPE_7__* next; TYPE_4__ age; } ;
typedef  TYPE_3__ drm_savage_buf_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int SAVAGE_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAVAGE_STATUS_WORD1 ; 
 scalar_t__ TEST_AGE (TYPE_4__*,int,unsigned int) ; 
 int /*<<< orphan*/  UPDATE_EVENT_COUNTER () ; 

__attribute__((used)) static struct drm_buf *savage_freelist_get(struct drm_device * dev)
{
	drm_savage_private_t *dev_priv = dev->dev_private;
	drm_savage_buf_priv_t *tail = dev_priv->tail.prev;
	uint16_t event;
	unsigned int wrap;
	DRM_DEBUG("\n");

	UPDATE_EVENT_COUNTER();
	if (dev_priv->status_ptr)
		event = dev_priv->status_ptr[1] & 0xffff;
	else
		event = SAVAGE_READ(SAVAGE_STATUS_WORD1) & 0xffff;
	wrap = dev_priv->event_wrap;
	if (event > dev_priv->event_counter)
		wrap--;		/* hardware hasn't passed the last wrap yet */

	DRM_DEBUG("   tail=0x%04x %d\n", tail->age.event, tail->age.wrap);
	DRM_DEBUG("   head=0x%04x %d\n", event, wrap);

	if (tail->buf && (TEST_AGE(&tail->age, event, wrap) || event == 0)) {
		drm_savage_buf_priv_t *next = tail->next;
		drm_savage_buf_priv_t *prev = tail->prev;
		prev->next = next;
		next->prev = prev;
		tail->next = tail->prev = NULL;
		return tail->buf;
	}

	DRM_DEBUG("returning NULL, tail->buf=%p!\n", tail->buf);
	return NULL;
}