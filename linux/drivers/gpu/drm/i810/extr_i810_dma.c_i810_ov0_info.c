#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  overlay_physical; int /*<<< orphan*/  overlay_offset; } ;
typedef  TYPE_1__ drm_i810_private_t ;
struct TYPE_4__ {int /*<<< orphan*/  physical; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ drm_i810_overlay_t ;

/* Variables and functions */

__attribute__((used)) static int i810_ov0_info(struct drm_device *dev, void *data,
			 struct drm_file *file_priv)
{
	drm_i810_private_t *dev_priv = (drm_i810_private_t *) dev->dev_private;
	drm_i810_overlay_t *ov = data;

	ov->offset = dev_priv->overlay_offset;
	ov->physical = dev_priv->overlay_physical;

	return 0;
}