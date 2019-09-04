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
struct omap_vout_device {scalar_t__* buf_virt_addr; scalar_t__* buf_phy_addr; int /*<<< orphan*/  buffer_size; scalar_t__ vid; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_vout_free_buffer (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video1_bufsize ; 
 int video1_numbuffers ; 
 int /*<<< orphan*/  video2_bufsize ; 
 int video2_numbuffers ; 

void omap_vout_free_buffers(struct omap_vout_device *vout)
{
	int i, numbuffers;

	/* Allocate memory for the buffers */
	numbuffers = (vout->vid) ?  video2_numbuffers : video1_numbuffers;
	vout->buffer_size = (vout->vid) ? video2_bufsize : video1_bufsize;

	for (i = 0; i < numbuffers; i++) {
		omap_vout_free_buffer(vout->buf_virt_addr[i],
				vout->buffer_size);
		vout->buf_phy_addr[i] = 0;
		vout->buf_virt_addr[i] = 0;
	}
}