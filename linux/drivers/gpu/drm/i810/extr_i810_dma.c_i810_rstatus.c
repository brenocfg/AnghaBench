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
typedef  scalar_t__ u32 ;
struct drm_file {int dummy; } ;
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_2__ {scalar_t__ hw_status_page; } ;
typedef  TYPE_1__ drm_i810_private_t ;

/* Variables and functions */

__attribute__((used)) static int i810_rstatus(struct drm_device *dev, void *data,
			struct drm_file *file_priv)
{
	drm_i810_private_t *dev_priv = (drm_i810_private_t *) dev->dev_private;

	return (int)(((u32 *) (dev_priv->hw_status_page))[4]);
}