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
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct soc_camera_host {struct sh_mobile_ceu_dev* priv; } ;
struct soc_camera_device {TYPE_2__* current_fmt; int /*<<< orphan*/  parent; } ;
struct sh_mobile_ceu_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* host_fmt; } ;
struct TYPE_3__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLFCR ; 
 int EINVAL ; 
#define  V4L2_CID_SHARPNESS 132 
#define  V4L2_PIX_FMT_NV12 131 
#define  V4L2_PIX_FMT_NV16 130 
#define  V4L2_PIX_FMT_NV21 129 
#define  V4L2_PIX_FMT_NV61 128 
 int /*<<< orphan*/  ceu_write (struct sh_mobile_ceu_dev*,int /*<<< orphan*/ ,int) ; 
 struct soc_camera_device* ctrl_to_icd (struct v4l2_ctrl*) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_mobile_ceu_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct soc_camera_device *icd = ctrl_to_icd(ctrl);
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct sh_mobile_ceu_dev *pcdev = ici->priv;

	switch (ctrl->id) {
	case V4L2_CID_SHARPNESS:
		switch (icd->current_fmt->host_fmt->fourcc) {
		case V4L2_PIX_FMT_NV12:
		case V4L2_PIX_FMT_NV21:
		case V4L2_PIX_FMT_NV16:
		case V4L2_PIX_FMT_NV61:
			ceu_write(pcdev, CLFCR, !ctrl->val);
			return 0;
		}
		break;
	}

	return -EINVAL;
}