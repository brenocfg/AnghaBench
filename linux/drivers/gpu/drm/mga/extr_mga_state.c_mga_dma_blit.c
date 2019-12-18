#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {TYPE_2__* dev_private; } ;
struct TYPE_7__ {scalar_t__ nbox; int /*<<< orphan*/  dirty; } ;
typedef  TYPE_1__ drm_mga_sarea_t ;
struct TYPE_8__ {TYPE_1__* sarea_priv; } ;
typedef  TYPE_2__ drm_mga_private_t ;
struct TYPE_9__ {int /*<<< orphan*/  dstorg; int /*<<< orphan*/  srcorg; } ;
typedef  TYPE_3__ drm_mga_blit_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 scalar_t__ MGA_NR_SAREA_CLIPRECTS ; 
 int /*<<< orphan*/  MGA_UPLOAD_CONTEXT ; 
 int /*<<< orphan*/  WRAP_TEST_WITH_RETURN (TYPE_2__*) ; 
 int /*<<< orphan*/  mga_dma_dispatch_blit (struct drm_device*,TYPE_3__*) ; 
 scalar_t__ mga_verify_blit (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mga_dma_blit(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_mga_private_t *dev_priv = dev->dev_private;
	drm_mga_sarea_t *sarea_priv = dev_priv->sarea_priv;
	drm_mga_blit_t *blit = data;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	if (sarea_priv->nbox > MGA_NR_SAREA_CLIPRECTS)
		sarea_priv->nbox = MGA_NR_SAREA_CLIPRECTS;

	if (mga_verify_blit(dev_priv, blit->srcorg, blit->dstorg))
		return -EINVAL;

	WRAP_TEST_WITH_RETURN(dev_priv);

	mga_dma_dispatch_blit(dev, blit);

	/* Make sure we restore the 3D state next time.
	 */
	dev_priv->sarea_priv->dirty |= MGA_UPLOAD_CONTEXT;

	return 0;
}