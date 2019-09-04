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
struct shmob_drm_device {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {struct shmob_drm_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  shmob_drm_crtc_enable_vblank (struct shmob_drm_device*,int) ; 

__attribute__((used)) static void shmob_drm_disable_vblank(struct drm_crtc *crtc)
{
	struct shmob_drm_device *sdev = crtc->dev->dev_private;

	shmob_drm_crtc_enable_vblank(sdev, false);
}