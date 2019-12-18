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
struct osd_info {int dummy; } ;
struct ivtv {int /*<<< orphan*/  v4l2_cap; TYPE_2__* streams; int /*<<< orphan*/  ivtvfb_restore; TYPE_3__* osd_info; int /*<<< orphan*/  osd_video_pbase; } ;
struct TYPE_6__ {int /*<<< orphan*/  ivtvfb_info; int /*<<< orphan*/  video_pbase; } ;
struct TYPE_4__ {int /*<<< orphan*/  device_caps; } ;
struct TYPE_5__ {TYPE_1__ vdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  IVTVFB_ERR (char*,...) ; 
 size_t IVTV_DEC_STREAM_TYPE_MPG ; 
 size_t IVTV_DEC_STREAM_TYPE_YUV ; 
 int /*<<< orphan*/  V4L2_CAP_VIDEO_OUTPUT_OVERLAY ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  ivtv_udma_alloc (struct ivtv*) ; 
 int /*<<< orphan*/  ivtvfb_blank (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ivtvfb_card_id ; 
 scalar_t__ ivtvfb_force_pat ; 
 int ivtvfb_init_io (struct ivtv*) ; 
 int ivtvfb_init_vidmode (struct ivtv*) ; 
 int /*<<< orphan*/  ivtvfb_release_buffers (struct ivtv*) ; 
 int /*<<< orphan*/  ivtvfb_restore ; 
 int /*<<< orphan*/  ivtvfb_set_par (int /*<<< orphan*/ *) ; 
 TYPE_3__* kzalloc (int,int) ; 
 scalar_t__ pat_enabled () ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ register_framebuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ivtvfb_init_card(struct ivtv *itv)
{
	int rc;

#ifdef CONFIG_X86_64
	if (pat_enabled()) {
		if (ivtvfb_force_pat) {
			pr_info("PAT is enabled. Write-combined framebuffer caching will be disabled.\n");
			pr_info("To enable caching, boot with nopat kernel parameter\n");
		} else {
			pr_warn("ivtvfb needs PAT disabled for write-combined framebuffer caching.\n");
			pr_warn("Boot with nopat kernel parameter to use caching, or use the\n");
			pr_warn("force_pat module parameter to run with caching disabled\n");
			return -ENODEV;
		}
	}
#endif

	if (itv->osd_info) {
		IVTVFB_ERR("Card %d already initialised\n", ivtvfb_card_id);
		return -EBUSY;
	}

	itv->osd_info = kzalloc(sizeof(struct osd_info),
					GFP_KERNEL|__GFP_NOWARN);
	if (itv->osd_info == NULL) {
		IVTVFB_ERR("Failed to allocate memory for osd_info\n");
		return -ENOMEM;
	}

	/* Find & setup the OSD buffer */
	rc = ivtvfb_init_io(itv);
	if (rc) {
		ivtvfb_release_buffers(itv);
		return rc;
	}

	/* Set the startup video mode information */
	if ((rc = ivtvfb_init_vidmode(itv))) {
		ivtvfb_release_buffers(itv);
		return rc;
	}

	/* Register the framebuffer */
	if (register_framebuffer(&itv->osd_info->ivtvfb_info) < 0) {
		ivtvfb_release_buffers(itv);
		return -EINVAL;
	}

	itv->osd_video_pbase = itv->osd_info->video_pbase;

	/* Set the card to the requested mode */
	ivtvfb_set_par(&itv->osd_info->ivtvfb_info);

	/* Set color 0 to black */
	write_reg(0, 0x02a30);
	write_reg(0, 0x02a34);

	/* Enable the osd */
	ivtvfb_blank(FB_BLANK_UNBLANK, &itv->osd_info->ivtvfb_info);

	/* Enable restart */
	itv->ivtvfb_restore = ivtvfb_restore;

	/* Allocate DMA */
	ivtv_udma_alloc(itv);
	itv->streams[IVTV_DEC_STREAM_TYPE_YUV].vdev.device_caps |=
		V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
	itv->streams[IVTV_DEC_STREAM_TYPE_MPG].vdev.device_caps |=
		V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
	itv->v4l2_cap |= V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
	return 0;

}