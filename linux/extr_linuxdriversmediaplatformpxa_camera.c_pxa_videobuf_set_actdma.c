#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pxa_camera_dev {int dummy; } ;
struct pxa_buffer {int active_dma; int nb_planes; } ;

/* Variables and functions */
 int DMA_U ; 
 int DMA_V ; 
 int DMA_Y ; 

__attribute__((used)) static void pxa_videobuf_set_actdma(struct pxa_camera_dev *pcdev,
				    struct pxa_buffer *buf)
{
	buf->active_dma = DMA_Y;
	if (buf->nb_planes == 3)
		buf->active_dma |= DMA_U | DMA_V;
}