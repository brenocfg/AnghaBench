#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_pix_format {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  pixelformat; int /*<<< orphan*/  field; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_5__ {struct v4l2_pix_format pix; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct TYPE_6__ {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct pxa_camera_dev {TYPE_4__* current_fmt; TYPE_2__ current_pix; } ;
struct file {int dummy; } ;
struct TYPE_8__ {TYPE_3__* host_fmt; } ;
struct TYPE_7__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcdev_to_dev (struct pxa_camera_dev*) ; 
 struct pxa_camera_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int pxac_vidioc_g_fmt_vid_cap(struct file *filp, void *priv,
				    struct v4l2_format *f)
{
	struct pxa_camera_dev *pcdev = video_drvdata(filp);
	struct v4l2_pix_format *pix = &f->fmt.pix;

	pix->width		= pcdev->current_pix.width;
	pix->height		= pcdev->current_pix.height;
	pix->bytesperline	= pcdev->current_pix.bytesperline;
	pix->sizeimage		= pcdev->current_pix.sizeimage;
	pix->field		= pcdev->current_pix.field;
	pix->pixelformat	= pcdev->current_fmt->host_fmt->fourcc;
	pix->colorspace		= pcdev->current_pix.colorspace;
	dev_dbg(pcdev_to_dev(pcdev), "current_fmt->fourcc: 0x%08x\n",
		pcdev->current_fmt->host_fmt->fourcc);
	return 0;
}