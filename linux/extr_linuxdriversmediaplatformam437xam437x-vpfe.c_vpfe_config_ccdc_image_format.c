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
struct TYPE_4__ {int field; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_5__ {TYPE_1__ pix; } ;
struct TYPE_6__ {TYPE_2__ fmt; } ;
struct vpfe_device {int /*<<< orphan*/  ccdc; TYPE_3__ fmt; int /*<<< orphan*/  bpp; int /*<<< orphan*/  crop; } ;
typedef  enum ccdc_frmfmt { ____Placeholder_ccdc_frmfmt } ccdc_frmfmt ;

/* Variables and functions */
 int /*<<< orphan*/  CCDC_BUFTYPE_FLD_INTERLEAVED ; 
 int /*<<< orphan*/  CCDC_BUFTYPE_FLD_SEPARATED ; 
 int CCDC_FRMFMT_INTERLACED ; 
 int CCDC_FRMFMT_PROGRESSIVE ; 
 int EINVAL ; 
#define  V4L2_FIELD_INTERLACED 130 
#define  V4L2_FIELD_NONE 129 
#define  V4L2_FIELD_SEQ_TB 128 
 int /*<<< orphan*/  print_fourcc (int /*<<< orphan*/ ) ; 
 int vpfe_ccdc_set_buftype (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vpfe_ccdc_set_frame_format (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vpfe_ccdc_set_image_window (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vpfe_ccdc_set_pixel_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpfe_dbg (int,struct vpfe_device*,char*,...) ; 
 int /*<<< orphan*/  vpfe_err (struct vpfe_device*,char*) ; 

__attribute__((used)) static int vpfe_config_ccdc_image_format(struct vpfe_device *vpfe)
{
	enum ccdc_frmfmt frm_fmt = CCDC_FRMFMT_INTERLACED;
	int ret = 0;

	vpfe_dbg(2, vpfe, "vpfe_config_ccdc_image_format\n");

	vpfe_dbg(1, vpfe, "pixelformat: %s\n",
		print_fourcc(vpfe->fmt.fmt.pix.pixelformat));

	if (vpfe_ccdc_set_pixel_format(&vpfe->ccdc,
			vpfe->fmt.fmt.pix.pixelformat) < 0) {
		vpfe_err(vpfe, "couldn't set pix format in ccdc\n");
		return -EINVAL;
	}

	/* configure the image window */
	vpfe_ccdc_set_image_window(&vpfe->ccdc, &vpfe->crop, vpfe->bpp);

	switch (vpfe->fmt.fmt.pix.field) {
	case V4L2_FIELD_INTERLACED:
		/* do nothing, since it is default */
		ret = vpfe_ccdc_set_buftype(
				&vpfe->ccdc,
				CCDC_BUFTYPE_FLD_INTERLEAVED);
		break;

	case V4L2_FIELD_NONE:
		frm_fmt = CCDC_FRMFMT_PROGRESSIVE;
		/* buffer type only applicable for interlaced scan */
		break;

	case V4L2_FIELD_SEQ_TB:
		ret = vpfe_ccdc_set_buftype(
				&vpfe->ccdc,
				CCDC_BUFTYPE_FLD_SEPARATED);
		break;

	default:
		return -EINVAL;
	}

	if (ret)
		return ret;

	return vpfe_ccdc_set_frame_format(&vpfe->ccdc, frm_fmt);
}