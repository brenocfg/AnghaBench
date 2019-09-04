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
struct nouveau_drm {struct drm_device* dev; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
typedef  enum mode_set_atomic { ____Placeholder_mode_set_atomic } mode_set_atomic ;

/* Variables and functions */
 int ENTER_ATOMIC_MODE_SET ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_fbcon_accel_restore (struct drm_device*) ; 
 int /*<<< orphan*/  nouveau_fbcon_accel_save_disable (struct drm_device*) ; 
 int nv04_crtc_do_mode_set_base (struct drm_crtc*,struct drm_framebuffer*,int,int,int) ; 

__attribute__((used)) static int
nv04_crtc_mode_set_base_atomic(struct drm_crtc *crtc,
			       struct drm_framebuffer *fb,
			       int x, int y, enum mode_set_atomic state)
{
	struct nouveau_drm *drm = nouveau_drm(crtc->dev);
	struct drm_device *dev = drm->dev;

	if (state == ENTER_ATOMIC_MODE_SET)
		nouveau_fbcon_accel_save_disable(dev);
	else
		nouveau_fbcon_accel_restore(dev);

	return nv04_crtc_do_mode_set_base(crtc, fb, x, y, true);
}