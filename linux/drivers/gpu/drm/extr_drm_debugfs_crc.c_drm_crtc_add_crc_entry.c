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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_crtc_crc_entry {int has_frame_counter; int /*<<< orphan*/  crcs; int /*<<< orphan*/  frame; } ;
struct drm_crtc_crc {int head; int tail; int overflow; int values_cnt; int /*<<< orphan*/  wq; int /*<<< orphan*/  lock; struct drm_crtc_crc_entry* entries; } ;
struct drm_crtc {struct drm_crtc_crc crc; } ;

/* Variables and functions */
 int CIRC_SPACE (int,int,int) ; 
 int DRM_CRC_ENTRIES_NR ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int drm_crtc_add_crc_entry(struct drm_crtc *crtc, bool has_frame,
			   uint32_t frame, uint32_t *crcs)
{
	struct drm_crtc_crc *crc = &crtc->crc;
	struct drm_crtc_crc_entry *entry;
	int head, tail;
	unsigned long flags;

	spin_lock_irqsave(&crc->lock, flags);

	/* Caller may not have noticed yet that userspace has stopped reading */
	if (!crc->entries) {
		spin_unlock_irqrestore(&crc->lock, flags);
		return -EINVAL;
	}

	head = crc->head;
	tail = crc->tail;

	if (CIRC_SPACE(head, tail, DRM_CRC_ENTRIES_NR) < 1) {
		bool was_overflow = crc->overflow;

		crc->overflow = true;
		spin_unlock_irqrestore(&crc->lock, flags);

		if (!was_overflow)
			DRM_ERROR("Overflow of CRC buffer, userspace reads too slow.\n");

		return -ENOBUFS;
	}

	entry = &crc->entries[head];
	entry->frame = frame;
	entry->has_frame_counter = has_frame;
	memcpy(&entry->crcs, crcs, sizeof(*crcs) * crc->values_cnt);

	head = (head + 1) & (DRM_CRC_ENTRIES_NR - 1);
	crc->head = head;

	spin_unlock_irqrestore(&crc->lock, flags);

	wake_up_interruptible(&crc->wq);

	return 0;
}