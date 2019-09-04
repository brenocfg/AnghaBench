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
struct TYPE_10__ {int frm_fmt; int /*<<< orphan*/  stdid; } ;
struct TYPE_9__ {int storage_mode; int hpitch; int /*<<< orphan*/  stdid; } ;
struct vpif_params {TYPE_5__ std_info; TYPE_4__ video_params; } ;
struct video_obj {scalar_t__ buf_field; } ;
struct TYPE_6__ {int field; unsigned int sizeimage; unsigned int bytesperline; } ;
struct TYPE_7__ {TYPE_1__ pix; } ;
struct TYPE_8__ {TYPE_2__ fmt; } ;
struct common_obj {unsigned int ytop_off; unsigned int ybtm_off; unsigned int ctop_off; unsigned int cbtm_off; TYPE_3__ fmt; } ;
struct channel_obj {struct vpif_params vpifparams; struct video_obj video; struct common_obj* common; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;

/* Variables and functions */
 scalar_t__ V4L2_FIELD_ANY ; 
 scalar_t__ V4L2_FIELD_INTERLACED ; 
 scalar_t__ V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_FIELD_SEQ_BT ; 
 scalar_t__ V4L2_FIELD_SEQ_TB ; 
 size_t VPIF_VIDEO_INDEX ; 

__attribute__((used)) static void vpif_calculate_offsets(struct channel_obj *ch)
{
	struct common_obj *common = &ch->common[VPIF_VIDEO_INDEX];
	struct vpif_params *vpifparams = &ch->vpifparams;
	enum v4l2_field field = common->fmt.fmt.pix.field;
	struct video_obj *vid_ch = &ch->video;
	unsigned int hpitch, sizeimage;

	if (V4L2_FIELD_ANY == common->fmt.fmt.pix.field) {
		if (ch->vpifparams.std_info.frm_fmt)
			vid_ch->buf_field = V4L2_FIELD_NONE;
		else
			vid_ch->buf_field = V4L2_FIELD_INTERLACED;
	} else {
		vid_ch->buf_field = common->fmt.fmt.pix.field;
	}

	sizeimage = common->fmt.fmt.pix.sizeimage;

	hpitch = common->fmt.fmt.pix.bytesperline;
	if ((V4L2_FIELD_NONE == vid_ch->buf_field) ||
	    (V4L2_FIELD_INTERLACED == vid_ch->buf_field)) {
		common->ytop_off = 0;
		common->ybtm_off = hpitch;
		common->ctop_off = sizeimage / 2;
		common->cbtm_off = sizeimage / 2 + hpitch;
	} else if (V4L2_FIELD_SEQ_TB == vid_ch->buf_field) {
		common->ytop_off = 0;
		common->ybtm_off = sizeimage / 4;
		common->ctop_off = sizeimage / 2;
		common->cbtm_off = common->ctop_off + sizeimage / 4;
	} else if (V4L2_FIELD_SEQ_BT == vid_ch->buf_field) {
		common->ybtm_off = 0;
		common->ytop_off = sizeimage / 4;
		common->cbtm_off = sizeimage / 2;
		common->ctop_off = common->cbtm_off + sizeimage / 4;
	}

	if ((V4L2_FIELD_NONE == vid_ch->buf_field) ||
	    (V4L2_FIELD_INTERLACED == vid_ch->buf_field)) {
		vpifparams->video_params.storage_mode = 1;
	} else {
		vpifparams->video_params.storage_mode = 0;
	}

	if (ch->vpifparams.std_info.frm_fmt == 1) {
		vpifparams->video_params.hpitch =
		    common->fmt.fmt.pix.bytesperline;
	} else {
		if ((field == V4L2_FIELD_ANY) ||
			(field == V4L2_FIELD_INTERLACED))
			vpifparams->video_params.hpitch =
			    common->fmt.fmt.pix.bytesperline * 2;
		else
			vpifparams->video_params.hpitch =
			    common->fmt.fmt.pix.bytesperline;
	}

	ch->vpifparams.video_params.stdid = ch->vpifparams.std_info.stdid;
}