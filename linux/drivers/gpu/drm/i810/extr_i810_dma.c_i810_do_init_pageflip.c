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
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_4__ {int page_flipping; scalar_t__ current_page; TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_i810_private_t ;
struct TYPE_3__ {scalar_t__ pf_current_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 

__attribute__((used)) static void i810_do_init_pageflip(struct drm_device *dev)
{
	drm_i810_private_t *dev_priv = dev->dev_private;

	DRM_DEBUG("\n");
	dev_priv->page_flipping = 1;
	dev_priv->current_page = 0;
	dev_priv->sarea_priv->pf_current_page = dev_priv->current_page;
}