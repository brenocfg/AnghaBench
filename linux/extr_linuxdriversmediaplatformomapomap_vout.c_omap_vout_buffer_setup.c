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
typedef  void* u32 ;
struct videobuf_queue {scalar_t__ type; struct omap_vout_device* priv_data; } ;
struct omapvideo_info {scalar_t__ rotation_type; } ;
struct TYPE_3__ {int width; int height; } ;
struct omap_vout_device {scalar_t__ vid; scalar_t__ memory; int bpp; unsigned int buffer_size; unsigned int buffer_allocated; void** buf_phy_addr; void** buf_virt_addr; scalar_t__* smsshado_phy_addr; scalar_t__* smsshado_virt_addr; int /*<<< orphan*/  smsshado_size; TYPE_2__* vid_dev; TYPE_1__ pix; struct omapvideo_info vid_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ OMAP_VIDEO1 ; 
 unsigned int PAGE_ALIGN (int) ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_MEMORY_MMAP ; 
 scalar_t__ VOUT_ROT_NONE ; 
 scalar_t__ VOUT_ROT_VRFB ; 
 int /*<<< orphan*/  is_rotation_enabled (struct omap_vout_device*) ; 
 void* omap_vout_alloc_buffer (unsigned int,void**) ; 
 int /*<<< orphan*/  omap_vout_free_buffer (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ omap_vout_vrfb_buffer_setup (struct omap_vout_device*,unsigned int*,int) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int video1_bufsize ; 
 int video1_numbuffers ; 
 int video2_bufsize ; 
 int video2_numbuffers ; 

__attribute__((used)) static int omap_vout_buffer_setup(struct videobuf_queue *q, unsigned int *count,
			  unsigned int *size)
{
	int startindex = 0, i, j;
	u32 phy_addr = 0, virt_addr = 0;
	struct omap_vout_device *vout = q->priv_data;
	struct omapvideo_info *ovid = &vout->vid_info;
	int vid_max_buf_size;

	if (!vout)
		return -EINVAL;

	vid_max_buf_size = vout->vid == OMAP_VIDEO1 ? video1_bufsize :
		video2_bufsize;

	if (V4L2_BUF_TYPE_VIDEO_OUTPUT != q->type)
		return -EINVAL;

	startindex = (vout->vid == OMAP_VIDEO1) ?
		video1_numbuffers : video2_numbuffers;
	if (V4L2_MEMORY_MMAP == vout->memory && *count < startindex)
		*count = startindex;

	if (ovid->rotation_type == VOUT_ROT_VRFB) {
		if (omap_vout_vrfb_buffer_setup(vout, count, startindex))
			return -ENOMEM;
	}

	if (V4L2_MEMORY_MMAP != vout->memory)
		return 0;

	/* Now allocated the V4L2 buffers */
	*size = PAGE_ALIGN(vout->pix.width * vout->pix.height * vout->bpp);
	startindex = (vout->vid == OMAP_VIDEO1) ?
		video1_numbuffers : video2_numbuffers;

	/* Check the size of the buffer */
	if (*size > vid_max_buf_size) {
		v4l2_err(&vout->vid_dev->v4l2_dev,
				"buffer allocation mismatch [%u] [%u]\n",
				*size, vout->buffer_size);
		return -ENOMEM;
	}

	for (i = startindex; i < *count; i++) {
		vout->buffer_size = *size;

		virt_addr = omap_vout_alloc_buffer(vout->buffer_size,
				&phy_addr);
		if (!virt_addr) {
			if (ovid->rotation_type == VOUT_ROT_NONE)
				break;

			if (!is_rotation_enabled(vout))
				break;

			/* Free the VRFB buffers if no space for V4L2 buffers */
			for (j = i; j < *count; j++) {
				omap_vout_free_buffer(vout->smsshado_virt_addr[j],
						      vout->smsshado_size);
				vout->smsshado_virt_addr[j] = 0;
				vout->smsshado_phy_addr[j] = 0;
			}
		}
		vout->buf_virt_addr[i] = virt_addr;
		vout->buf_phy_addr[i] = phy_addr;
	}
	*count = vout->buffer_allocated = i;

	return 0;
}