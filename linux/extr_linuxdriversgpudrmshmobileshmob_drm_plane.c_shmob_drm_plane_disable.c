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
struct shmob_drm_plane {int /*<<< orphan*/  index; int /*<<< orphan*/ * format; } ;
struct shmob_drm_device {int dummy; } ;
struct drm_plane {TYPE_1__* dev; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct TYPE_2__ {struct shmob_drm_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDBnBSIFR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (struct shmob_drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct shmob_drm_plane* to_shmob_plane (struct drm_plane*) ; 

__attribute__((used)) static int shmob_drm_plane_disable(struct drm_plane *plane,
				   struct drm_modeset_acquire_ctx *ctx)
{
	struct shmob_drm_plane *splane = to_shmob_plane(plane);
	struct shmob_drm_device *sdev = plane->dev->dev_private;

	splane->format = NULL;

	lcdc_write(sdev, LDBnBSIFR(splane->index), 0);
	return 0;
}