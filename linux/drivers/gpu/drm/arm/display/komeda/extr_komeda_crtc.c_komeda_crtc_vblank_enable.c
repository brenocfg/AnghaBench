#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct komeda_dev {TYPE_2__* funcs; } ;
struct komeda_crtc {TYPE_3__* master; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* on_off_vblank ) (struct komeda_dev*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {struct komeda_dev* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct komeda_dev*,int /*<<< orphan*/ ,int) ; 
 struct komeda_crtc* to_kcrtc (struct drm_crtc*) ; 

__attribute__((used)) static int komeda_crtc_vblank_enable(struct drm_crtc *crtc)
{
	struct komeda_dev *mdev = crtc->dev->dev_private;
	struct komeda_crtc *kcrtc = to_kcrtc(crtc);

	mdev->funcs->on_off_vblank(mdev, kcrtc->master->id, true);
	return 0;
}