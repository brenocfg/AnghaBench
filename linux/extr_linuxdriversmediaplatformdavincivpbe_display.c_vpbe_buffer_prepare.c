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
struct TYPE_3__ {int /*<<< orphan*/  sizeimage; } ;
struct vpbe_layer {TYPE_1__ pix_fmt; TYPE_2__* disp_dev; } ;
struct vpbe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct vb2_queue {int dummy; } ;
struct vb2_buffer {struct vb2_queue* vb2_queue; } ;
struct TYPE_4__ {struct vpbe_device* vpbe_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 struct vpbe_layer* vb2_get_drv_priv (struct vb2_queue*) ; 
 scalar_t__ vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpbe_buffer_prepare(struct vb2_buffer *vb)
{
	struct vb2_queue *q = vb->vb2_queue;
	struct vpbe_layer *layer = vb2_get_drv_priv(q);
	struct vpbe_device *vpbe_dev = layer->disp_dev->vpbe_dev;
	unsigned long addr;

	v4l2_dbg(1, debug, &vpbe_dev->v4l2_dev,
				"vpbe_buffer_prepare\n");

	vb2_set_plane_payload(vb, 0, layer->pix_fmt.sizeimage);
	if (vb2_get_plane_payload(vb, 0) > vb2_plane_size(vb, 0))
		return -EINVAL;

	addr = vb2_dma_contig_plane_dma_addr(vb, 0);
	if (!IS_ALIGNED(addr, 8)) {
		v4l2_err(&vpbe_dev->v4l2_dev,
			 "buffer_prepare:offset is not aligned to 32 bytes\n");
		return -EINVAL;
	}
	return 0;
}