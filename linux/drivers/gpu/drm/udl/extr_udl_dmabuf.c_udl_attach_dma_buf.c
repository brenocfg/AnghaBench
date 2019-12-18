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
struct udl_drm_dmabuf_attachment {int /*<<< orphan*/  dir; } ;
struct dma_buf_attachment {struct udl_drm_dmabuf_attachment* priv; TYPE_1__* dmabuf; int /*<<< orphan*/  dev; } ;
struct dma_buf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  DRM_DEBUG_PRIME (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 struct udl_drm_dmabuf_attachment* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udl_attach_dma_buf(struct dma_buf *dmabuf,
			      struct dma_buf_attachment *attach)
{
	struct udl_drm_dmabuf_attachment *udl_attach;

	DRM_DEBUG_PRIME("[DEV:%s] size:%zd\n", dev_name(attach->dev),
			attach->dmabuf->size);

	udl_attach = kzalloc(sizeof(*udl_attach), GFP_KERNEL);
	if (!udl_attach)
		return -ENOMEM;

	udl_attach->dir = DMA_NONE;
	attach->priv = udl_attach;

	return 0;
}