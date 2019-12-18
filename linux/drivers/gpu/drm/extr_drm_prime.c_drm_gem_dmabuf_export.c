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
struct drm_device {int dummy; } ;
struct dma_buf_export_info {int /*<<< orphan*/  priv; } ;
struct dma_buf {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dma_buf*) ; 
 struct dma_buf* dma_buf_export (struct dma_buf_export_info*) ; 
 int /*<<< orphan*/  drm_dev_get (struct drm_device*) ; 
 int /*<<< orphan*/  drm_gem_object_get (int /*<<< orphan*/ ) ; 

struct dma_buf *drm_gem_dmabuf_export(struct drm_device *dev,
				      struct dma_buf_export_info *exp_info)
{
	struct dma_buf *dma_buf;

	dma_buf = dma_buf_export(exp_info);
	if (IS_ERR(dma_buf))
		return dma_buf;

	drm_dev_get(dev);
	drm_gem_object_get(exp_info->priv);

	return dma_buf;
}