#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct regmap {int dummy; } ;
struct TYPE_14__ {int fourcc; int dctrl_dview; TYPE_4__* sd_format; } ;
struct TYPE_8__ {int sizeimage; int height; int width; } ;
struct TYPE_9__ {TYPE_1__ pix; } ;
struct TYPE_10__ {TYPE_2__ fmt; } ;
struct isc_device {int /*<<< orphan*/  awb_lock; TYPE_7__ config; TYPE_6__* cur_frm; TYPE_3__ fmt; struct regmap* regmap; } ;
typedef  int dma_addr_t ;
struct TYPE_12__ {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_13__ {TYPE_5__ vb; } ;
struct TYPE_11__ {int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_CTRLEN ; 
 int ISC_CTRL_CAPTURE ; 
 int /*<<< orphan*/  ISC_DAD0 ; 
 int /*<<< orphan*/  ISC_DAD1 ; 
 int /*<<< orphan*/  ISC_DAD2 ; 
 int /*<<< orphan*/  ISC_DCTRL ; 
 int ISC_DCTRL_IE_IS ; 
 int /*<<< orphan*/  ISC_IS_FORMAT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_PFE_CFG0 ; 
 int ISC_PFE_CFG0_COLEN ; 
 int ISC_PFE_CFG0_ROWEN ; 
 int /*<<< orphan*/  ISC_PFE_CFG1 ; 
 int ISC_PFE_CFG1_COLMAX (int) ; 
 int ISC_PFE_CFG1_COLMAX_MASK ; 
 int ISC_PFE_CFG1_COLMIN (int /*<<< orphan*/ ) ; 
 int ISC_PFE_CFG1_COLMIN_MASK ; 
 int /*<<< orphan*/  ISC_PFE_CFG2 ; 
 int ISC_PFE_CFG2_ROWMAX (int) ; 
 int ISC_PFE_CFG2_ROWMAX_MASK ; 
 int ISC_PFE_CFG2_ROWMIN (int /*<<< orphan*/ ) ; 
 int ISC_PFE_CFG2_ROWMIN_MASK ; 
#define  V4L2_PIX_FMT_YUV420 129 
#define  V4L2_PIX_FMT_YUV422P 128 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isc_start_dma(struct isc_device *isc)
{
	struct regmap *regmap = isc->regmap;
	u32 sizeimage = isc->fmt.fmt.pix.sizeimage;
	u32 dctrl_dview;
	dma_addr_t addr0;
	u32 h, w;

	h = isc->fmt.fmt.pix.height;
	w = isc->fmt.fmt.pix.width;

	/*
	 * In case the sensor is not RAW, it will output a pixel (12-16 bits)
	 * with two samples on the ISC Data bus (which is 8-12)
	 * ISC will count each sample, so, we need to multiply these values
	 * by two, to get the real number of samples for the required pixels.
	 */
	if (!ISC_IS_FORMAT_RAW(isc->config.sd_format->mbus_code)) {
		h <<= 1;
		w <<= 1;
	}

	/*
	 * We limit the column/row count that the ISC will output according
	 * to the configured resolution that we want.
	 * This will avoid the situation where the sensor is misconfigured,
	 * sending more data, and the ISC will just take it and DMA to memory,
	 * causing corruption.
	 */
	regmap_write(regmap, ISC_PFE_CFG1,
		     (ISC_PFE_CFG1_COLMIN(0) & ISC_PFE_CFG1_COLMIN_MASK) |
		     (ISC_PFE_CFG1_COLMAX(w - 1) & ISC_PFE_CFG1_COLMAX_MASK));

	regmap_write(regmap, ISC_PFE_CFG2,
		     (ISC_PFE_CFG2_ROWMIN(0) & ISC_PFE_CFG2_ROWMIN_MASK) |
		     (ISC_PFE_CFG2_ROWMAX(h - 1) & ISC_PFE_CFG2_ROWMAX_MASK));

	regmap_update_bits(regmap, ISC_PFE_CFG0,
			   ISC_PFE_CFG0_COLEN | ISC_PFE_CFG0_ROWEN,
			   ISC_PFE_CFG0_COLEN | ISC_PFE_CFG0_ROWEN);

	addr0 = vb2_dma_contig_plane_dma_addr(&isc->cur_frm->vb.vb2_buf, 0);
	regmap_write(regmap, ISC_DAD0, addr0);

	switch (isc->config.fourcc) {
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

	dctrl_dview = isc->config.dctrl_dview;

	regmap_write(regmap, ISC_DCTRL, dctrl_dview | ISC_DCTRL_IE_IS);
	spin_lock(&isc->awb_lock);
	regmap_write(regmap, ISC_CTRLEN, ISC_CTRL_CAPTURE);
	spin_unlock(&isc->awb_lock);
}