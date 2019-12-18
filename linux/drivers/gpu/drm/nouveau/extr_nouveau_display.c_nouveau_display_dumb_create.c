#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct nouveau_cli {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  base; } ;
struct nouveau_bo {TYPE_4__ bo; } ;
struct drm_mode_create_dumb {int pitch; int width; int bpp; int size; int height; int /*<<< orphan*/  handle; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ ram_size; } ;
struct TYPE_7__ {TYPE_1__ info; } ;
struct TYPE_8__ {TYPE_2__ device; } ;
struct TYPE_10__ {TYPE_3__ client; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOUVEAU_GEM_DOMAIN_GART ; 
 int /*<<< orphan*/  NOUVEAU_GEM_DOMAIN_VRAM ; 
 int PAGE_SIZE ; 
 int drm_gem_handle_create (struct drm_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 struct nouveau_cli* nouveau_cli (struct drm_file*) ; 
 TYPE_5__* nouveau_drm (struct drm_device*) ; 
 int nouveau_gem_new (struct nouveau_cli*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nouveau_bo**) ; 
 void* roundup (int,int) ; 

int
nouveau_display_dumb_create(struct drm_file *file_priv, struct drm_device *dev,
			    struct drm_mode_create_dumb *args)
{
	struct nouveau_cli *cli = nouveau_cli(file_priv);
	struct nouveau_bo *bo;
	uint32_t domain;
	int ret;

	args->pitch = roundup(args->width * (args->bpp / 8), 256);
	args->size = args->pitch * args->height;
	args->size = roundup(args->size, PAGE_SIZE);

	/* Use VRAM if there is any ; otherwise fallback to system memory */
	if (nouveau_drm(dev)->client.device.info.ram_size != 0)
		domain = NOUVEAU_GEM_DOMAIN_VRAM;
	else
		domain = NOUVEAU_GEM_DOMAIN_GART;

	ret = nouveau_gem_new(cli, args->size, 0, domain, 0, 0, &bo);
	if (ret)
		return ret;

	ret = drm_gem_handle_create(file_priv, &bo->bo.base, &args->handle);
	drm_gem_object_put_unlocked(&bo->bo.base);
	return ret;
}