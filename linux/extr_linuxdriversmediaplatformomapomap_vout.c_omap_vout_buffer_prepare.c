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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct videobuf_queue {struct omap_vout_device* priv_data; } ;
struct videobuf_buffer {scalar_t__ state; int width; int height; int size; int field; scalar_t__ memory; scalar_t__ baddr; size_t i; } ;
struct omapvideo_info {scalar_t__ rotation_type; } ;
struct TYPE_4__ {int width; int height; } ;
struct omap_vout_device {int bpp; scalar_t__* buf_phy_addr; int /*<<< orphan*/ ** queued_buf_addr; TYPE_2__* vid_dev; scalar_t__* buf_virt_addr; TYPE_1__ pix; struct omapvideo_info vid_info; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_3__ v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 scalar_t__ V4L2_MEMORY_USERPTR ; 
 scalar_t__ VIDEOBUF_NEEDS_INIT ; 
 scalar_t__ VIDEOBUF_PREPARED ; 
 scalar_t__ VOUT_ROT_VRFB ; 
 unsigned long dma_map_single (int /*<<< orphan*/ ,void*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,unsigned long) ; 
 int omap_vout_get_userptr (struct videobuf_buffer*,scalar_t__,int /*<<< orphan*/ *) ; 
 int omap_vout_prepare_vrfb (struct omap_vout_device*,struct videobuf_buffer*) ; 
 int /*<<< orphan*/  v4l2_err (TYPE_3__*,char*) ; 

__attribute__((used)) static int omap_vout_buffer_prepare(struct videobuf_queue *q,
			struct videobuf_buffer *vb,
			enum v4l2_field field)
{
	struct omap_vout_device *vout = q->priv_data;
	struct omapvideo_info *ovid = &vout->vid_info;

	if (VIDEOBUF_NEEDS_INIT == vb->state) {
		vb->width = vout->pix.width;
		vb->height = vout->pix.height;
		vb->size = vb->width * vb->height * vout->bpp;
		vb->field = field;
	}
	vb->state = VIDEOBUF_PREPARED;
	/* if user pointer memory mechanism is used, get the physical
	 * address of the buffer
	 */
	if (V4L2_MEMORY_USERPTR == vb->memory) {
		int ret;

		if (0 == vb->baddr)
			return -EINVAL;
		/* Physical address */
		ret = omap_vout_get_userptr(vb, vb->baddr,
				(u32 *)&vout->queued_buf_addr[vb->i]);
		if (ret < 0)
			return ret;
	} else {
		unsigned long addr, dma_addr;
		unsigned long size;

		addr = (unsigned long) vout->buf_virt_addr[vb->i];
		size = (unsigned long) vb->size;

		dma_addr = dma_map_single(vout->vid_dev->v4l2_dev.dev, (void *) addr,
				size, DMA_TO_DEVICE);
		if (dma_mapping_error(vout->vid_dev->v4l2_dev.dev, dma_addr))
			v4l2_err(&vout->vid_dev->v4l2_dev,
				 "dma_map_single failed\n");

		vout->queued_buf_addr[vb->i] = (u8 *)vout->buf_phy_addr[vb->i];
	}

	if (ovid->rotation_type == VOUT_ROT_VRFB)
		return omap_vout_prepare_vrfb(vout, vb);
	else
		return 0;
}