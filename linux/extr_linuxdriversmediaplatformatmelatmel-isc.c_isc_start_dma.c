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
typedef  int u32 ;
struct v4l2_pix_format {int sizeimage; int pixelformat; } ;
struct regmap {int dummy; } ;
struct TYPE_6__ {struct v4l2_pix_format pix; } ;
struct TYPE_7__ {TYPE_1__ fmt; } ;
struct isc_device {TYPE_5__* current_fmt; TYPE_4__* cur_frm; TYPE_2__ fmt; struct regmap* regmap; } ;
struct fmt_config {int dctrl_dview; } ;
typedef  int dma_addr_t ;
struct TYPE_10__ {int /*<<< orphan*/  fourcc; } ;
struct TYPE_8__ {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_9__ {TYPE_3__ vb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_CTRLEN ; 
 int ISC_CTRL_CAPTURE ; 
 int /*<<< orphan*/  ISC_DAD0 ; 
 int /*<<< orphan*/  ISC_DAD1 ; 
 int /*<<< orphan*/  ISC_DAD2 ; 
 int /*<<< orphan*/  ISC_DCTRL ; 
 int ISC_DCTRL_DVIEW_PACKED ; 
 int ISC_DCTRL_IE_IS ; 
#define  V4L2_PIX_FMT_YUV420 129 
#define  V4L2_PIX_FMT_YUV422P 128 
 struct fmt_config* get_fmt_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sensor_is_preferred (TYPE_5__*) ; 
 int vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isc_start_dma(struct isc_device *isc)
{
	struct regmap *regmap = isc->regmap;
	struct v4l2_pix_format *pixfmt = &isc->fmt.fmt.pix;
	u32 sizeimage = pixfmt->sizeimage;
	struct fmt_config *config = get_fmt_config(isc->current_fmt->fourcc);
	u32 dctrl_dview;
	dma_addr_t addr0;

	addr0 = vb2_dma_contig_plane_dma_addr(&isc->cur_frm->vb.vb2_buf, 0);
	regmap_write(regmap, ISC_DAD0, addr0);

	switch (pixfmt->pixelformat) {
	case V4L2_PIX_FMT_YUV420:
		regmap_write(regmap, ISC_DAD1, addr0 + (sizeimage * 2) / 3);
		regmap_write(regmap, ISC_DAD2, addr0 + (sizeimage * 5) / 6);
		break;
	case V4L2_PIX_FMT_YUV422P:
		regmap_write(regmap, ISC_DAD1, addr0 + sizeimage / 2);
		regmap_write(regmap, ISC_DAD2, addr0 + (sizeimage * 3) / 4);
		break;
	default:
		break;
	}

	if (sensor_is_preferred(isc->current_fmt))
		dctrl_dview = ISC_DCTRL_DVIEW_PACKED;
	else
		dctrl_dview = config->dctrl_dview;

	regmap_write(regmap, ISC_DCTRL, dctrl_dview | ISC_DCTRL_IE_IS);
	regmap_write(regmap, ISC_CTRLEN, ISC_CTRL_CAPTURE);
}