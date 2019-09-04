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
struct sg_table {int dummy; } ;
struct dma_buf_attachment {TYPE_1__* dmabuf; int /*<<< orphan*/  dev; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_PRIME (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udl_unmap_dma_buf(struct dma_buf_attachment *attach,
			      struct sg_table *sgt,
			      enum dma_data_direction dir)
{
	/* Nothing to do. */
	DRM_DEBUG_PRIME("[DEV:%s] size:%zd dir:%d\n", dev_name(attach->dev),
			attach->dmabuf->size, dir);
}