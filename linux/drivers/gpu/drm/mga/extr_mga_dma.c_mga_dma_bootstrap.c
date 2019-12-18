#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_6__ {TYPE_1__* agp_textures; } ;
typedef  TYPE_2__ drm_mga_private_t ;
struct TYPE_7__ {int agp_mode; scalar_t__ texture_size; scalar_t__ texture_handle; } ;
typedef  TYPE_3__ drm_mga_dma_bootstrap_t ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FULL_CLEANUP ; 
 int /*<<< orphan*/  mga_do_cleanup_dma (struct drm_device*,int /*<<< orphan*/ ) ; 
 int mga_do_dma_bootstrap (struct drm_device*,TYPE_3__*) ; 

int mga_dma_bootstrap(struct drm_device *dev, void *data,
		      struct drm_file *file_priv)
{
	drm_mga_dma_bootstrap_t *bootstrap = data;
	int err;
	static const int modes[] = { 0, 1, 2, 2, 4, 4, 4, 4 };
	const drm_mga_private_t *const dev_priv =
		(drm_mga_private_t *) dev->dev_private;

	err = mga_do_dma_bootstrap(dev, bootstrap);
	if (err) {
		mga_do_cleanup_dma(dev, FULL_CLEANUP);
		return err;
	}

	if (dev_priv->agp_textures != NULL) {
		bootstrap->texture_handle = dev_priv->agp_textures->offset;
		bootstrap->texture_size = dev_priv->agp_textures->size;
	} else {
		bootstrap->texture_handle = 0;
		bootstrap->texture_size = 0;
	}

	bootstrap->agp_mode = modes[bootstrap->agp_mode & 0x07];

	return err;
}