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
struct drm_device {int dummy; } ;
struct drm_buf {scalar_t__ used; int /*<<< orphan*/ * file_priv; scalar_t__ pending; scalar_t__ waiting; } ;

/* Variables and functions */

void drm_legacy_free_buffer(struct drm_device *dev, struct drm_buf * buf)
{
	if (!buf)
		return;

	buf->waiting = 0;
	buf->pending = 0;
	buf->file_priv = NULL;
	buf->used = 0;
}