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
typedef  unsigned int u32 ;
struct soc_camera_host {struct sh_mobile_ceu_dev* priv; } ;
struct soc_camera_device {unsigned int user_width; unsigned int user_height; unsigned int bytesperline; int /*<<< orphan*/  parent; TYPE_2__* current_fmt; struct sh_mobile_ceu_cam* host_priv; } ;
struct sh_mobile_ceu_dev {scalar_t__ field; int /*<<< orphan*/  is_16bit; scalar_t__ image_mode; } ;
struct sh_mobile_ceu_cam {unsigned int ceu_left; unsigned int ceu_top; unsigned int width; unsigned int height; } ;
struct TYPE_4__ {TYPE_1__* host_fmt; } ;
struct TYPE_3__ {int packing; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAMOR ; 
 int /*<<< orphan*/  CAPWR ; 
 int /*<<< orphan*/  CDWDR ; 
 int /*<<< orphan*/  CFSZR ; 
#define  SOC_MBUS_PACKING_2X8_PADHI 128 
 scalar_t__ V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ceu_write (struct sh_mobile_ceu_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_geo (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_mobile_ceu_set_rect(struct soc_camera_device *icd)
{
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct sh_mobile_ceu_cam *cam = icd->host_priv;
	struct sh_mobile_ceu_dev *pcdev = ici->priv;
	unsigned int height, width, cdwdr_width, in_width, in_height;
	unsigned int left_offset, top_offset;
	u32 camor;

	dev_geo(icd->parent, "Crop %ux%u@%u:%u\n",
		icd->user_width, icd->user_height, cam->ceu_left, cam->ceu_top);

	left_offset	= cam->ceu_left;
	top_offset	= cam->ceu_top;

	WARN_ON(icd->user_width & 3 || icd->user_height & 3);

	width = icd->user_width;

	if (pcdev->image_mode) {
		in_width = cam->width;
		if (!pcdev->is_16bit) {
			in_width *= 2;
			left_offset *= 2;
		}
	} else {
		unsigned int w_factor;

		switch (icd->current_fmt->host_fmt->packing) {
		case SOC_MBUS_PACKING_2X8_PADHI:
			w_factor = 2;
			break;
		default:
			w_factor = 1;
		}

		in_width = cam->width * w_factor;
		left_offset *= w_factor;
	}

	cdwdr_width = icd->bytesperline;

	height = icd->user_height;
	in_height = cam->height;
	if (V4L2_FIELD_NONE != pcdev->field) {
		height = (height / 2) & ~3;
		in_height /= 2;
		top_offset /= 2;
		cdwdr_width *= 2;
	}

	/* Set CAMOR, CAPWR, CFSZR, take care of CDWDR */
	camor = left_offset | (top_offset << 16);

	dev_geo(icd->parent,
		"CAMOR 0x%x, CAPWR 0x%x, CFSZR 0x%x, CDWDR 0x%x\n", camor,
		(in_height << 16) | in_width, (height << 16) | width,
		cdwdr_width);

	ceu_write(pcdev, CAMOR, camor);
	ceu_write(pcdev, CAPWR, (in_height << 16) | in_width);
	/* CFSZR clipping is applied _after_ the scaling filter (CFLCR) */
	ceu_write(pcdev, CFSZR, (height << 16) | width);
	ceu_write(pcdev, CDWDR, cdwdr_width);
}