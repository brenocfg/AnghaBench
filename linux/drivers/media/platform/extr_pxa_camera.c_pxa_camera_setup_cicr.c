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
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ height; scalar_t__ width; } ;
struct pxa_camera_dev {int platform_flags; int channels; int mclk_divisor; scalar_t__ base; TYPE_3__ current_pix; TYPE_2__* current_fmt; } ;
typedef  int __u32 ;
struct TYPE_5__ {TYPE_1__* host_fmt; } ;
struct TYPE_4__ {int bits_per_sample; } ;

/* Variables and functions */
 scalar_t__ CICR0 ; 
 int CICR0_DMAEN ; 
 int CICR0_ENB ; 
 int CICR0_IRQ_MASK ; 
 int CICR0_SIM_MP ; 
 int CICR0_SIM_SP ; 
 int CICR0_SL_CAP_EN ; 
 scalar_t__ CICR1 ; 
 int CICR1_COLOR_SP_VAL (int) ; 
 unsigned long CICR1_PPL_VAL (scalar_t__) ; 
 int CICR1_RGBT_CONV_VAL (int) ; 
 int CICR1_RGB_BPP_VAL (int) ; 
 int CICR1_TBIT ; 
 int CICR1_YCBCR_F ; 
 scalar_t__ CICR2 ; 
 scalar_t__ CICR3 ; 
 int CICR3_BFW_VAL (int /*<<< orphan*/ ) ; 
 int CICR3_LPF_VAL (scalar_t__) ; 
 scalar_t__ CICR4 ; 
 int CICR4_HSP ; 
 int CICR4_MCLK_EN ; 
 int CICR4_PCLK_EN ; 
 int CICR4_PCP ; 
 int CICR4_VSP ; 
 int PXA_CAMERA_MASTER ; 
 int PXA_CAMERA_MCLK_EN ; 
 int PXA_CAMERA_PCLK_EN ; 
 unsigned long V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 unsigned long V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 unsigned long V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
#define  V4L2_PIX_FMT_RGB555 134 
#define  V4L2_PIX_FMT_RGB565 133 
#define  V4L2_PIX_FMT_UYVY 132 
#define  V4L2_PIX_FMT_VYUY 131 
#define  V4L2_PIX_FMT_YUV422P 130 
#define  V4L2_PIX_FMT_YUYV 129 
#define  V4L2_PIX_FMT_YVYU 128 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 int /*<<< orphan*/  g_skip_top_lines ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  sensor ; 
 int sensor_call (struct pxa_camera_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void pxa_camera_setup_cicr(struct pxa_camera_dev *pcdev,
				  unsigned long flags, __u32 pixfmt)
{
	unsigned long dw, bpp;
	u32 cicr0, cicr1, cicr2, cicr3, cicr4 = 0, y_skip_top;
	int ret = sensor_call(pcdev, sensor, g_skip_top_lines, &y_skip_top);

	if (ret < 0)
		y_skip_top = 0;

	/*
	 * Datawidth is now guaranteed to be equal to one of the three values.
	 * We fix bit-per-pixel equal to data-width...
	 */
	switch (pcdev->current_fmt->host_fmt->bits_per_sample) {
	case 10:
		dw = 4;
		bpp = 0x40;
		break;
	case 9:
		dw = 3;
		bpp = 0x20;
		break;
	default:
		/*
		 * Actually it can only be 8 now,
		 * default is just to silence compiler warnings
		 */
	case 8:
		dw = 2;
		bpp = 0;
	}

	if (pcdev->platform_flags & PXA_CAMERA_PCLK_EN)
		cicr4 |= CICR4_PCLK_EN;
	if (pcdev->platform_flags & PXA_CAMERA_MCLK_EN)
		cicr4 |= CICR4_MCLK_EN;
	if (flags & V4L2_MBUS_PCLK_SAMPLE_FALLING)
		cicr4 |= CICR4_PCP;
	if (flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		cicr4 |= CICR4_HSP;
	if (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
		cicr4 |= CICR4_VSP;

	cicr0 = __raw_readl(pcdev->base + CICR0);
	if (cicr0 & CICR0_ENB)
		__raw_writel(cicr0 & ~CICR0_ENB, pcdev->base + CICR0);

	cicr1 = CICR1_PPL_VAL(pcdev->current_pix.width - 1) | bpp | dw;

	switch (pixfmt) {
	case V4L2_PIX_FMT_YUV422P:
		pcdev->channels = 3;
		cicr1 |= CICR1_YCBCR_F;
		/*
		 * Normally, pxa bus wants as input UYVY format. We allow all
		 * reorderings of the YUV422 format, as no processing is done,
		 * and the YUV stream is just passed through without any
		 * transformation. Note that UYVY is the only format that
		 * should be used if pxa framebuffer Overlay2 is used.
		 */
		/* fall through */
	case V4L2_PIX_FMT_UYVY:
	case V4L2_PIX_FMT_VYUY:
	case V4L2_PIX_FMT_YUYV:
	case V4L2_PIX_FMT_YVYU:
		cicr1 |= CICR1_COLOR_SP_VAL(2);
		break;
	case V4L2_PIX_FMT_RGB555:
		cicr1 |= CICR1_RGB_BPP_VAL(1) | CICR1_RGBT_CONV_VAL(2) |
			CICR1_TBIT | CICR1_COLOR_SP_VAL(1);
		break;
	case V4L2_PIX_FMT_RGB565:
		cicr1 |= CICR1_COLOR_SP_VAL(1) | CICR1_RGB_BPP_VAL(2);
		break;
	}

	cicr2 = 0;
	cicr3 = CICR3_LPF_VAL(pcdev->current_pix.height - 1) |
		CICR3_BFW_VAL(min((u32)255, y_skip_top));
	cicr4 |= pcdev->mclk_divisor;

	__raw_writel(cicr1, pcdev->base + CICR1);
	__raw_writel(cicr2, pcdev->base + CICR2);
	__raw_writel(cicr3, pcdev->base + CICR3);
	__raw_writel(cicr4, pcdev->base + CICR4);

	/* CIF interrupts are not used, only DMA */
	cicr0 = (cicr0 & CICR0_ENB) | (pcdev->platform_flags & PXA_CAMERA_MASTER ?
		CICR0_SIM_MP : (CICR0_SL_CAP_EN | CICR0_SIM_SP));
	cicr0 |= CICR0_DMAEN | CICR0_IRQ_MASK;
	__raw_writel(cicr0, pcdev->base + CICR0);
}