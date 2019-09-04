#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_2__ {int pixelformat; int width; int height; } ;
struct sh_vou_device {TYPE_1__ pix; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
#define  V4L2_PIX_FMT_NV12 129 
#define  V4L2_PIX_FMT_NV16 128 
 int /*<<< orphan*/  VOUAD1R ; 
 int /*<<< orphan*/  VOUAD2R ; 
 int /*<<< orphan*/  sh_vou_reg_m_write (struct sh_vou_device*,int /*<<< orphan*/ ,int) ; 
 int vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_vou_schedule_next(struct sh_vou_device *vou_dev,
				 struct vb2_v4l2_buffer *vbuf)
{
	dma_addr_t addr1, addr2;

	addr1 = vb2_dma_contig_plane_dma_addr(&vbuf->vb2_buf, 0);
	switch (vou_dev->pix.pixelformat) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV16:
		addr2 = addr1 + vou_dev->pix.width * vou_dev->pix.height;
		break;
	default:
		addr2 = 0;
	}

	sh_vou_reg_m_write(vou_dev, VOUAD1R, addr1);
	sh_vou_reg_m_write(vou_dev, VOUAD2R, addr2);
}