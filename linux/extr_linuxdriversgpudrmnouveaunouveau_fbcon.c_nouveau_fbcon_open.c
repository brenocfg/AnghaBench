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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct nouveau_fbdev {TYPE_1__ helper; } ;
struct nouveau_drm {TYPE_2__* dev; } ;
struct fb_info {struct nouveau_fbdev* par; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EACCES ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nouveau_fbcon_open(struct fb_info *info, int user)
{
	struct nouveau_fbdev *fbcon = info->par;
	struct nouveau_drm *drm = nouveau_drm(fbcon->helper.dev);
	int ret = pm_runtime_get_sync(drm->dev->dev);
	if (ret < 0 && ret != -EACCES)
		return ret;
	return 0;
}