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
struct vb2_buffer {int dummy; } ;
struct v4l2_pix_format {unsigned int height; scalar_t__ bytesperline; } ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 unsigned int vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dma_addr_t cedrus_buf_addr(struct vb2_buffer *buf,
					 struct v4l2_pix_format *pix_fmt,
					 unsigned int plane)
{
	dma_addr_t addr = vb2_dma_contig_plane_dma_addr(buf, 0);

	return addr + (pix_fmt ? (dma_addr_t)pix_fmt->bytesperline *
	       pix_fmt->height * plane : 0);
}