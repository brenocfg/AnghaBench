#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vpif_channel_config_params {int width; int height; scalar_t__ frm_fmt; } ;
struct vpif_params {struct vpif_channel_config_params std_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  height; } ;
struct TYPE_7__ {TYPE_1__ bt; } ;
struct video_obj {scalar_t__ stdid; TYPE_2__ dv_timings; } ;
struct TYPE_8__ {int width; int height; int sizeimage; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_9__ {TYPE_3__ pix; } ;
struct TYPE_10__ {TYPE_4__ fmt; } ;
struct common_obj {int height; int width; TYPE_5__ fmt; } ;
struct channel_obj {struct vpif_params vpifparams; struct video_obj video; struct common_obj* common; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 int /*<<< orphan*/  V4L2_FIELD_INTERLACED ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_PIX_FMT_YUV422P ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ vpif_update_std_info (struct channel_obj*) ; 

__attribute__((used)) static int vpif_update_resolution(struct channel_obj *ch)
{
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	struct video_obj *vid_ch = &ch->video;
	struct vpif_params *vpifparams = &ch->vpifparams;
	struct vpif_channel_config_params *std_info = &vpifparams->std_info;

	if (!vid_ch->stdid && !vid_ch->dv_timings.bt.height)
		return -EINVAL;

	if (vid_ch->stdid) {
		if (vpif_update_std_info(ch))
			return -EINVAL;
	}

	common->fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUV422P;
	common->fmt.fmt.pix.width = std_info->width;
	common->fmt.fmt.pix.height = std_info->height;
	vpif_dbg(1, debug, "Pixel details: Width = %d,Height = %d\n",
			common->fmt.fmt.pix.width, common->fmt.fmt.pix.height);

	/* Set height and width paramateres */
	common->height = std_info->height;
	common->width = std_info->width;
	common->fmt.fmt.pix.sizeimage = common->height * common->width * 2;

	if (vid_ch->stdid)
		common->fmt.fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	else
		common->fmt.fmt.pix.colorspace = V4L2_COLORSPACE_REC709;

	if (ch->vpifparams.std_info.frm_fmt)
		common->fmt.fmt.pix.field = V4L2_FIELD_NONE;
	else
		common->fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

	return 0;
}