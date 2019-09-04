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
struct TYPE_6__ {int field; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_7__ {TYPE_1__ pix; } ;
struct TYPE_8__ {TYPE_2__ fmt; } ;
struct vpfe_device {TYPE_3__ fmt; int /*<<< orphan*/  crop; int /*<<< orphan*/  v4l2_dev; } ;
typedef  enum ccdc_frmfmt { ____Placeholder_ccdc_frmfmt } ccdc_frmfmt ;
struct TYPE_9__ {scalar_t__ (* set_pixel_format ) (int /*<<< orphan*/ ) ;int (* set_buftype ) (int /*<<< orphan*/ ) ;int (* set_frame_format ) (int) ;int /*<<< orphan*/  (* set_image_window ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {TYPE_4__ hw_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCDC_BUFTYPE_FLD_INTERLEAVED ; 
 int /*<<< orphan*/  CCDC_BUFTYPE_FLD_SEPARATED ; 
 int CCDC_FRMFMT_INTERLACED ; 
 int CCDC_FRMFMT_PROGRESSIVE ; 
 int EINVAL ; 
#define  V4L2_FIELD_INTERLACED 130 
#define  V4L2_FIELD_NONE 129 
#define  V4L2_FIELD_SEQ_TB 128 
 TYPE_5__* ccdc_dev ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int stub3 (int /*<<< orphan*/ ) ; 
 int stub4 (int /*<<< orphan*/ ) ; 
 int stub5 (int) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int vpfe_config_ccdc_image_format(struct vpfe_device *vpfe_dev)
{
	enum ccdc_frmfmt frm_fmt = CCDC_FRMFMT_INTERLACED;
	int ret = 0;

	if (ccdc_dev->hw_ops.set_pixel_format(
			vpfe_dev->fmt.fmt.pix.pixelformat) < 0) {
		v4l2_err(&vpfe_dev->v4l2_dev,
			"couldn't set pix format in ccdc\n");
		return -EINVAL;
	}
	/* configure the image window */
	ccdc_dev->hw_ops.set_image_window(&vpfe_dev->crop);

	switch (vpfe_dev->fmt.fmt.pix.field) {
	case V4L2_FIELD_INTERLACED:
		/* do nothing, since it is default */
		ret = ccdc_dev->hw_ops.set_buftype(
				CCDC_BUFTYPE_FLD_INTERLEAVED);
		break;
	case V4L2_FIELD_NONE:
		frm_fmt = CCDC_FRMFMT_PROGRESSIVE;
		/* buffer type only applicable for interlaced scan */
		break;
	case V4L2_FIELD_SEQ_TB:
		ret = ccdc_dev->hw_ops.set_buftype(
				CCDC_BUFTYPE_FLD_SEPARATED);
		break;
	default:
		return -EINVAL;
	}

	/* set the frame format */
	if (!ret)
		ret = ccdc_dev->hw_ops.set_frame_format(frm_fmt);
	return ret;
}