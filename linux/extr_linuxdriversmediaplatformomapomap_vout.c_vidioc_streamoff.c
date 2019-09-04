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
typedef  int u32 ;
struct omapvideo_info {int num_overlays; struct omap_overlay** overlays; } ;
struct omap_vout_device {int streaming; int /*<<< orphan*/  vbq; int /*<<< orphan*/  dma_queue; TYPE_1__* vid_dev; struct omapvideo_info vid_info; } ;
struct omap_overlay {int /*<<< orphan*/  (* disable ) (struct omap_overlay*) ;struct omap_dss_device* (* get_device ) (struct omap_overlay*) ;} ;
struct omap_dss_device {int dummy; } ;
struct file {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_2__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int DISPC_IRQ_EVSYNC_EVEN ; 
 int DISPC_IRQ_EVSYNC_ODD ; 
 int DISPC_IRQ_VSYNC ; 
 int DISPC_IRQ_VSYNC2 ; 
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_dispc_unregister_isr (int /*<<< orphan*/ ,struct omap_vout_device*,int) ; 
 int /*<<< orphan*/  omap_vout_isr ; 
 int omapvid_apply_changes (struct omap_vout_device*) ; 
 struct omap_dss_device* stub1 (struct omap_overlay*) ; 
 int /*<<< orphan*/  stub2 (struct omap_overlay*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int videobuf_streamoff (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_streamoff(struct file *file, void *fh, enum v4l2_buf_type i)
{
	u32 mask = 0;
	int ret = 0, j;
	struct omap_vout_device *vout = fh;
	struct omapvideo_info *ovid = &vout->vid_info;

	if (!vout->streaming)
		return -EINVAL;

	vout->streaming = false;
	mask = DISPC_IRQ_VSYNC | DISPC_IRQ_EVSYNC_EVEN | DISPC_IRQ_EVSYNC_ODD
		| DISPC_IRQ_VSYNC2;

	omap_dispc_unregister_isr(omap_vout_isr, vout, mask);

	for (j = 0; j < ovid->num_overlays; j++) {
		struct omap_overlay *ovl = ovid->overlays[j];
		struct omap_dss_device *dssdev = ovl->get_device(ovl);

		if (dssdev)
			ovl->disable(ovl);
	}

	/* Turn of the pipeline */
	ret = omapvid_apply_changes(vout);
	if (ret)
		v4l2_err(&vout->vid_dev->v4l2_dev,
			 "failed to change mode in streamoff\n");

	INIT_LIST_HEAD(&vout->dma_queue);
	ret = videobuf_streamoff(&vout->vbq);

	return ret;
}