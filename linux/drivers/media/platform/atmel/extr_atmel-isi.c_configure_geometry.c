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
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int width; int height; } ;
struct TYPE_7__ {TYPE_2__ pix; } ;
struct TYPE_8__ {TYPE_3__ fmt; } ;
struct atmel_isi {int enable_preview_path; TYPE_4__ fmt; TYPE_1__* current_fmt; } ;
struct TYPE_5__ {scalar_t__ fourcc; scalar_t__ swap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISI_CFG2 ; 
 int ISI_CFG2_IM_HSIZE_MASK ; 
 int ISI_CFG2_IM_HSIZE_OFFSET ; 
 int ISI_CFG2_IM_VSIZE_MASK ; 
 int ISI_CFG2_IM_VSIZE_OFFSET ; 
 int /*<<< orphan*/  ISI_CTRL ; 
 scalar_t__ ISI_CTRL_DIS ; 
 int /*<<< orphan*/  ISI_PDECF ; 
 scalar_t__ ISI_PDECF_NO_SAMPLING ; 
 int /*<<< orphan*/  ISI_PSIZE ; 
 int ISI_PSIZE_PREV_HSIZE_MASK ; 
 int ISI_PSIZE_PREV_HSIZE_OFFSET ; 
 int ISI_PSIZE_PREV_VSIZE_MASK ; 
 int ISI_PSIZE_PREV_VSIZE_OFFSET ; 
 scalar_t__ V4L2_PIX_FMT_RGB32 ; 
 scalar_t__ V4L2_PIX_FMT_RGB565 ; 
 int /*<<< orphan*/  isi_writel (struct atmel_isi*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void configure_geometry(struct atmel_isi *isi)
{
	u32 cfg2, psize;
	u32 fourcc = isi->current_fmt->fourcc;

	isi->enable_preview_path = fourcc == V4L2_PIX_FMT_RGB565 ||
				   fourcc == V4L2_PIX_FMT_RGB32;

	/* According to sensor's output format to set cfg2 */
	cfg2 = isi->current_fmt->swap;

	isi_writel(isi, ISI_CTRL, ISI_CTRL_DIS);
	/* Set width */
	cfg2 |= ((isi->fmt.fmt.pix.width - 1) << ISI_CFG2_IM_HSIZE_OFFSET) &
			ISI_CFG2_IM_HSIZE_MASK;
	/* Set height */
	cfg2 |= ((isi->fmt.fmt.pix.height - 1) << ISI_CFG2_IM_VSIZE_OFFSET)
			& ISI_CFG2_IM_VSIZE_MASK;
	isi_writel(isi, ISI_CFG2, cfg2);

	/* No down sampling, preview size equal to sensor output size */
	psize = ((isi->fmt.fmt.pix.width - 1) << ISI_PSIZE_PREV_HSIZE_OFFSET) &
		ISI_PSIZE_PREV_HSIZE_MASK;
	psize |= ((isi->fmt.fmt.pix.height - 1) << ISI_PSIZE_PREV_VSIZE_OFFSET) &
		ISI_PSIZE_PREV_VSIZE_MASK;
	isi_writel(isi, ISI_PSIZE, psize);
	isi_writel(isi, ISI_PDECF, ISI_PDECF_NO_SAMPLING);
}