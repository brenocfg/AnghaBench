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
struct vc4_dev {TYPE_1__* hvs; } ;
struct drm_device {struct vc4_dev* dev_private; } ;
struct device {int dummy; } ;
struct TYPE_4__ {scalar_t__ allocated; } ;
struct TYPE_3__ {int /*<<< orphan*/  lbm_mm; int /*<<< orphan*/  dlist_mm; TYPE_2__ mitchell_netravali_filter; } ;

/* Variables and functions */
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_mm_remove_node (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vc4_hvs_unbind(struct device *dev, struct device *master,
			   void *data)
{
	struct drm_device *drm = dev_get_drvdata(master);
	struct vc4_dev *vc4 = drm->dev_private;

	if (vc4->hvs->mitchell_netravali_filter.allocated)
		drm_mm_remove_node(&vc4->hvs->mitchell_netravali_filter);

	drm_mm_takedown(&vc4->hvs->dlist_mm);
	drm_mm_takedown(&vc4->hvs->lbm_mm);

	vc4->hvs = NULL;
}