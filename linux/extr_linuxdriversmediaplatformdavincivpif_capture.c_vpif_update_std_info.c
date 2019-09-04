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
struct TYPE_8__ {scalar_t__ if_type; } ;
struct vpif_channel_config_params {int capture_format; scalar_t__ hd_sd; int stdid; int width; int height; scalar_t__ frm_fmt; int /*<<< orphan*/  dv_timings; } ;
struct TYPE_7__ {int hpitch; scalar_t__ storage_mode; } ;
struct TYPE_6__ {int data_sz; } ;
struct vpif_params {TYPE_3__ iface; struct vpif_channel_config_params std_info; TYPE_2__ video_params; TYPE_1__ params; } ;
struct video_obj {int stdid; int /*<<< orphan*/  dv_timings; } ;
struct v4l2_pix_format {int width; int height; scalar_t__ field; scalar_t__ pixelformat; int sizeimage; int bytesperline; int /*<<< orphan*/  colorspace; } ;
struct TYPE_9__ {struct v4l2_pix_format pix; } ;
struct TYPE_10__ {int /*<<< orphan*/  type; TYPE_4__ fmt; } ;
struct common_obj {int width; int height; TYPE_5__ fmt; } ;
struct channel_obj {struct vpif_params vpifparams; struct video_obj video; struct common_obj* common; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_REC709 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SMPTE170M ; 
 scalar_t__ V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_PIX_FMT_NV16 ; 
 scalar_t__ V4L2_PIX_FMT_SBGGR8 ; 
 scalar_t__ V4L2_PIX_FMT_SGRBG10 ; 
 scalar_t__ VPIF_IF_BT656 ; 
 scalar_t__ VPIF_IF_RAW_BAYER ; 
 size_t VPIF_VIDEO_INDEX ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (struct vpif_channel_config_params*,struct vpif_channel_config_params const*,int) ; 
 int /*<<< orphan*/  memset (struct vpif_channel_config_params*,int /*<<< orphan*/ ,int) ; 
 struct vpif_channel_config_params* vpif_ch_params ; 
 int vpif_ch_params_count ; 
 int /*<<< orphan*/  vpif_dbg (int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vpif_update_std_info(struct channel_obj *ch)
{
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	struct vpif_params *vpifparams = &ch->vpifparams;
	const struct vpif_channel_config_params *config;
	struct vpif_channel_config_params *std_info = &vpifparams->std_info;
	struct video_obj *vid_ch = &ch->video;
	int index;
	struct v4l2_pix_format *pixfmt = &common->fmt.fmt.pix;

	vpif_dbg(2, debug, "vpif_update_std_info\n");

	/*
	 * if called after try_fmt or g_fmt, there will already be a size
	 * so use that by default.
	 */
	if (pixfmt->width && pixfmt->height) {
		if (pixfmt->field == V4L2_FIELD_ANY ||
		    pixfmt->field == V4L2_FIELD_NONE)
			pixfmt->field = V4L2_FIELD_NONE;

		vpifparams->iface.if_type = VPIF_IF_BT656;
		if (pixfmt->pixelformat == V4L2_PIX_FMT_SGRBG10 ||
		    pixfmt->pixelformat == V4L2_PIX_FMT_SBGGR8)
			vpifparams->iface.if_type = VPIF_IF_RAW_BAYER;

		if (pixfmt->pixelformat == V4L2_PIX_FMT_SGRBG10)
			vpifparams->params.data_sz = 1; /* 10 bits/pixel.  */

		/*
		 * For raw formats from camera sensors, we don't need
		 * the std_info from table lookup, so nothing else to do here.
		 */
		if (vpifparams->iface.if_type == VPIF_IF_RAW_BAYER) {
			memset(std_info, 0, sizeof(struct vpif_channel_config_params));
			vpifparams->std_info.capture_format = 1; /* CCD/raw mode */
			return 0;
		}
	}

	for (index = 0; index < vpif_ch_params_count; index++) {
		config = &vpif_ch_params[index];
		if (config->hd_sd == 0) {
			vpif_dbg(2, debug, "SD format\n");
			if (config->stdid & vid_ch->stdid) {
				memcpy(std_info, config, sizeof(*config));
				break;
			}
		} else {
			vpif_dbg(2, debug, "HD format\n");
			if (!memcmp(&config->dv_timings, &vid_ch->dv_timings,
				sizeof(vid_ch->dv_timings))) {
				memcpy(std_info, config, sizeof(*config));
				break;
			}
		}
	}

	/* standard not found */
	if (index == vpif_ch_params_count)
		return -EINVAL;

	common->fmt.fmt.pix.width = std_info->width;
	common->width = std_info->width;
	common->fmt.fmt.pix.height = std_info->height;
	common->height = std_info->height;
	common->fmt.fmt.pix.sizeimage = common->height * common->width * 2;
	common->fmt.fmt.pix.bytesperline = std_info->width;
	vpifparams->video_params.hpitch = std_info->width;
	vpifparams->video_params.storage_mode = std_info->frm_fmt;

	if (vid_ch->stdid)
		common->fmt.fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;
	else
		common->fmt.fmt.pix.colorspace = V4L2_COLORSPACE_REC709;

	if (ch->vpifparams.std_info.frm_fmt)
		common->fmt.fmt.pix.field = V4L2_FIELD_NONE;
	else
		common->fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

	if (ch->vpifparams.iface.if_type == VPIF_IF_RAW_BAYER)
		common->fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_SBGGR8;
	else
		common->fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV16;

	common->fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	return 0;
}