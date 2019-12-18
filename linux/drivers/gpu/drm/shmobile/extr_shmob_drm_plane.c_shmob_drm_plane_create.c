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
struct shmob_drm_plane {unsigned int index; int alpha; int /*<<< orphan*/  plane; } ;
struct shmob_drm_device {int /*<<< orphan*/  ddev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct shmob_drm_plane* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int drm_plane_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  formats ; 
 int /*<<< orphan*/  shmob_drm_plane_funcs ; 

int shmob_drm_plane_create(struct shmob_drm_device *sdev, unsigned int index)
{
	struct shmob_drm_plane *splane;
	int ret;

	splane = devm_kzalloc(sdev->dev, sizeof(*splane), GFP_KERNEL);
	if (splane == NULL)
		return -ENOMEM;

	splane->index = index;
	splane->alpha = 255;

	ret = drm_plane_init(sdev->ddev, &splane->plane, 1,
			     &shmob_drm_plane_funcs, formats,
			     ARRAY_SIZE(formats), false);

	return ret;
}