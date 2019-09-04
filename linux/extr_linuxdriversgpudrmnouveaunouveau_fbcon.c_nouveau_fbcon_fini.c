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
struct nouveau_drm {int /*<<< orphan*/ * fbcon; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_fbcon_accel_fini (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_fbcon_destroy (struct drm_device*,int /*<<< orphan*/ *) ; 

void
nouveau_fbcon_fini(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);

	if (!drm->fbcon)
		return;

	nouveau_fbcon_accel_fini(dev);
	nouveau_fbcon_destroy(dev, drm->fbcon);
	kfree(drm->fbcon);
	drm->fbcon = NULL;
}