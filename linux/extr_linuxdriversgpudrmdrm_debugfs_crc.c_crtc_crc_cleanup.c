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
struct drm_crtc_crc {int overflow; int opened; scalar_t__ values_cnt; scalar_t__ tail; scalar_t__ head; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crtc_crc_cleanup(struct drm_crtc_crc *crc)
{
	kfree(crc->entries);
	crc->overflow = false;
	crc->entries = NULL;
	crc->head = 0;
	crc->tail = 0;
	crc->values_cnt = 0;
	crc->opened = false;
}