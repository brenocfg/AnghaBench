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
struct saa7146_vv {scalar_t__ vflip; } ;
struct saa7146_video_dma {int pitch; scalar_t__ prot_addr; scalar_t__ base_even; scalar_t__ base_odd; } ;
struct saa7146_buf {TYPE_2__* pt; TYPE_1__* fmt; } ;
struct TYPE_4__ {scalar_t__ offset; } ;
struct TYPE_3__ {int height; int width; } ;

/* Variables and functions */

__attribute__((used)) static int calc_planar_420(struct saa7146_vv *vv, struct saa7146_buf *buf, struct saa7146_video_dma *vdma2, struct saa7146_video_dma *vdma3)
{
	int height = buf->fmt->height;
	int width = buf->fmt->width;

	vdma2->pitch	= width/2;
	vdma3->pitch	= width/2;

	if( 0 != vv->vflip ) {
		vdma2->prot_addr	= buf->pt[2].offset;
		vdma2->base_even	= ((vdma2->pitch/2)*height)+buf->pt[2].offset;
		vdma2->base_odd		= vdma2->base_even - (vdma2->pitch/2);

		vdma3->prot_addr	= buf->pt[1].offset;
		vdma3->base_even	= ((vdma3->pitch/2)*height)+buf->pt[1].offset;
		vdma3->base_odd		= vdma3->base_even - (vdma3->pitch/2);

	} else {
		vdma3->base_even	= buf->pt[2].offset;
		vdma3->base_odd		= vdma3->base_even + (vdma3->pitch);
		vdma3->prot_addr	= (vdma3->pitch/2)*height+buf->pt[2].offset;

		vdma2->base_even	= buf->pt[1].offset;
		vdma2->base_odd		= vdma2->base_even + (vdma2->pitch);
		vdma2->prot_addr	= (vdma2->pitch/2)*height+buf->pt[1].offset;
	}
	return 0;
}