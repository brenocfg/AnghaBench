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
struct nouveau_cli {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
struct nouveau_bo {TYPE_1__ bo; } ;
struct TYPE_4__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  tile_flags; int /*<<< orphan*/  tile_mode; int /*<<< orphan*/  domain; int /*<<< orphan*/  size; } ;
struct drm_nouveau_gem_new {TYPE_2__ info; int /*<<< orphan*/  align; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_handle_delete (struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct nouveau_cli* nouveau_cli (struct drm_file*) ; 
 int nouveau_gem_info (struct drm_file*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int nouveau_gem_new (struct nouveau_cli*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nouveau_bo**) ; 

int
nouveau_gem_ioctl_new(struct drm_device *dev, void *data,
		      struct drm_file *file_priv)
{
	struct nouveau_cli *cli = nouveau_cli(file_priv);
	struct drm_nouveau_gem_new *req = data;
	struct nouveau_bo *nvbo = NULL;
	int ret = 0;

	ret = nouveau_gem_new(cli, req->info.size, req->align,
			      req->info.domain, req->info.tile_mode,
			      req->info.tile_flags, &nvbo);
	if (ret)
		return ret;

	ret = drm_gem_handle_create(file_priv, &nvbo->bo.base,
				    &req->info.handle);
	if (ret == 0) {
		ret = nouveau_gem_info(file_priv, &nvbo->bo.base, &req->info);
		if (ret)
			drm_gem_handle_delete(file_priv, req->info.handle);
	}

	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put_unlocked(&nvbo->bo.base);
	return ret;
}