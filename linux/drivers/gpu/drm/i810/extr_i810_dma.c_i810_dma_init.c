#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  drm_i810_private_t ;
struct TYPE_3__ {int func; } ;
typedef  TYPE_1__ drm_i810_init_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  I810_CLEANUP_DMA 129 
#define  I810_INIT_DMA_1_4 128 
 int i810_dma_cleanup (struct drm_device*) ; 
 int i810_dma_initialize (struct drm_device*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i810_dma_init(struct drm_device *dev, void *data,
			 struct drm_file *file_priv)
{
	drm_i810_private_t *dev_priv;
	drm_i810_init_t *init = data;
	int retcode = 0;

	switch (init->func) {
	case I810_INIT_DMA_1_4:
		DRM_INFO("Using v1.4 init.\n");
		dev_priv = kmalloc(sizeof(drm_i810_private_t), GFP_KERNEL);
		if (dev_priv == NULL)
			return -ENOMEM;
		retcode = i810_dma_initialize(dev, dev_priv, init);
		break;

	case I810_CLEANUP_DMA:
		DRM_INFO("DMA Cleanup\n");
		retcode = i810_dma_cleanup(dev);
		break;
	default:
		return -EINVAL;
	}

	return retcode;
}