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
struct fsl_dcu_drm_device {int /*<<< orphan*/  regmap; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {TYPE_1__* dev; } ;
struct TYPE_2__ {struct fsl_dcu_drm_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCU_CTRLDESCLN (int,int) ; 
 unsigned int DCU_LAYER_EN ; 
 int fsl_dcu_drm_plane_index (struct drm_plane*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void fsl_dcu_drm_plane_atomic_disable(struct drm_plane *plane,
					     struct drm_plane_state *old_state)
{
	struct fsl_dcu_drm_device *fsl_dev = plane->dev->dev_private;
	unsigned int value;
	int index;

	index = fsl_dcu_drm_plane_index(plane);
	if (index < 0)
		return;

	regmap_read(fsl_dev->regmap, DCU_CTRLDESCLN(index, 4), &value);
	value &= ~DCU_LAYER_EN;
	regmap_write(fsl_dev->regmap, DCU_CTRLDESCLN(index, 4), value);
}