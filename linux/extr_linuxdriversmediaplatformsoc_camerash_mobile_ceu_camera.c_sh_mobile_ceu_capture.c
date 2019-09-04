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
typedef  int u32 ;
struct soc_camera_device {int bytesperline; int user_height; TYPE_4__* current_fmt; } ;
struct TYPE_5__ {struct soc_camera_device* icd; } ;
struct sh_mobile_ceu_dev {scalar_t__ field; TYPE_2__* active; int /*<<< orphan*/  complete; scalar_t__ frozen; TYPE_1__ ici; } ;
typedef  int dma_addr_t ;
struct TYPE_8__ {TYPE_3__* host_fmt; } ;
struct TYPE_7__ {int fourcc; } ;
struct TYPE_6__ {int /*<<< orphan*/  vb2_buf; } ;

/* Variables and functions */
 unsigned long CAPCR ; 
 unsigned long CAPSR ; 
 unsigned long CDACR ; 
 unsigned long CDAYR ; 
 unsigned long CDBCR ; 
 unsigned long CDBYR ; 
 unsigned long CEIER ; 
 unsigned long CETCR ; 
 int CEU_CAPCR_CTNCP ; 
 int CEU_CEIER_MASK ; 
 int CEU_CEIER_VBP ; 
 int CEU_CETCR_IGRW ; 
 int CEU_CETCR_MAGIC ; 
 int EIO ; 
 scalar_t__ V4L2_FIELD_INTERLACED_BT ; 
 scalar_t__ V4L2_FIELD_NONE ; 
#define  V4L2_PIX_FMT_NV12 131 
#define  V4L2_PIX_FMT_NV16 130 
#define  V4L2_PIX_FMT_NV21 129 
#define  V4L2_PIX_FMT_NV61 128 
 int ceu_read (struct sh_mobile_ceu_dev*,unsigned long) ; 
 int /*<<< orphan*/  ceu_write (struct sh_mobile_ceu_dev*,unsigned long,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sh_mobile_ceu_soft_reset (struct sh_mobile_ceu_dev*) ; 
 int vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_mobile_ceu_capture(struct sh_mobile_ceu_dev *pcdev)
{
	struct soc_camera_device *icd = pcdev->ici.icd;
	dma_addr_t phys_addr_top, phys_addr_bottom;
	unsigned long top1, top2;
	unsigned long bottom1, bottom2;
	u32 status;
	bool planar;
	int ret = 0;

	/*
	 * The hardware is _very_ picky about this sequence. Especially
	 * the CEU_CETCR_MAGIC value. It seems like we need to acknowledge
	 * several not-so-well documented interrupt sources in CETCR.
	 */
	ceu_write(pcdev, CEIER, ceu_read(pcdev, CEIER) & ~CEU_CEIER_MASK);
	status = ceu_read(pcdev, CETCR);
	ceu_write(pcdev, CETCR, ~status & CEU_CETCR_MAGIC);
	if (!pcdev->frozen)
		ceu_write(pcdev, CEIER, ceu_read(pcdev, CEIER) | CEU_CEIER_MASK);
	ceu_write(pcdev, CAPCR, ceu_read(pcdev, CAPCR) & ~CEU_CAPCR_CTNCP);
	ceu_write(pcdev, CETCR, CEU_CETCR_MAGIC ^ CEU_CETCR_IGRW);

	/*
	 * When a VBP interrupt occurs, a capture end interrupt does not occur
	 * and the image of that frame is not captured correctly. So, soft reset
	 * is needed here.
	 */
	if (status & CEU_CEIER_VBP) {
		sh_mobile_ceu_soft_reset(pcdev);
		ret = -EIO;
	}

	if (pcdev->frozen) {
		complete(&pcdev->complete);
		return ret;
	}

	if (!pcdev->active)
		return ret;

	if (V4L2_FIELD_INTERLACED_BT == pcdev->field) {
		top1	= CDBYR;
		top2	= CDBCR;
		bottom1	= CDAYR;
		bottom2	= CDACR;
	} else {
		top1	= CDAYR;
		top2	= CDACR;
		bottom1	= CDBYR;
		bottom2	= CDBCR;
	}

	phys_addr_top =
		vb2_dma_contig_plane_dma_addr(&pcdev->active->vb2_buf, 0);

	switch (icd->current_fmt->host_fmt->fourcc) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		planar = true;
		break;
	default:
		planar = false;
	}

	ceu_write(pcdev, top1, phys_addr_top);
	if (V4L2_FIELD_NONE != pcdev->field) {
		phys_addr_bottom = phys_addr_top + icd->bytesperline;
		ceu_write(pcdev, bottom1, phys_addr_bottom);
	}

	if (planar) {
		phys_addr_top += icd->bytesperline * icd->user_height;
		ceu_write(pcdev, top2, phys_addr_top);
		if (V4L2_FIELD_NONE != pcdev->field) {
			phys_addr_bottom = phys_addr_top + icd->bytesperline;
			ceu_write(pcdev, bottom2, phys_addr_bottom);
		}
	}

	ceu_write(pcdev, CAPSR, 0x1); /* start capture */

	return ret;
}