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
struct fsl_dcu_drm_device {int /*<<< orphan*/  dev; TYPE_2__* soc; } ;
struct drm_plane {TYPE_1__* dev; } ;
struct TYPE_4__ {unsigned int total_layer; } ;
struct TYPE_3__ {struct fsl_dcu_drm_device* dev_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int drm_plane_index (struct drm_plane*) ; 

__attribute__((used)) static int fsl_dcu_drm_plane_index(struct drm_plane *plane)
{
	struct fsl_dcu_drm_device *fsl_dev = plane->dev->dev_private;
	unsigned int total_layer = fsl_dev->soc->total_layer;
	unsigned int index;

	index = drm_plane_index(plane);
	if (index < total_layer)
		return total_layer - index - 1;

	dev_err(fsl_dev->dev, "No more layer left\n");
	return -EINVAL;
}