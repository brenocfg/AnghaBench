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
struct mtk_drm_private {int /*<<< orphan*/ * drm; scalar_t__ num_pipes; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mtk_drm_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dev_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_drm_kms_deinit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_drm_unbind(struct device *dev)
{
	struct mtk_drm_private *private = dev_get_drvdata(dev);

	drm_dev_unregister(private->drm);
	mtk_drm_kms_deinit(private->drm);
	drm_dev_put(private->drm);
	private->num_pipes = 0;
	private->drm = NULL;
}