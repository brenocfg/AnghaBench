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
struct drm_crtc_crc {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CIRC_CNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_CRC_ENTRIES_NR ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crtc_crc_data_count(struct drm_crtc_crc *crc)
{
	assert_spin_locked(&crc->lock);
	return CIRC_CNT(crc->head, crc->tail, DRM_CRC_ENTRIES_NR);
}