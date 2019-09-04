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
struct omap_vout_device {scalar_t__ vid; int buffer_allocated; scalar_t__* buf_phy_addr; scalar_t__* buf_virt_addr; int /*<<< orphan*/  buffer_size; } ;

/* Variables and functions */
 scalar_t__ OMAP_VIDEO1 ; 
 int /*<<< orphan*/  omap_vout_free_buffer (scalar_t__,int /*<<< orphan*/ ) ; 
 int video1_numbuffers ; 
 int video2_numbuffers ; 

__attribute__((used)) static void omap_vout_free_extra_buffers(struct omap_vout_device *vout)
{
	int num_buffers = 0, i;

	num_buffers = (vout->vid == OMAP_VIDEO1) ?
		video1_numbuffers : video2_numbuffers;

	for (i = num_buffers; i < vout->buffer_allocated; i++) {
		if (vout->buf_virt_addr[i])
			omap_vout_free_buffer(vout->buf_virt_addr[i],
					vout->buffer_size);

		vout->buf_virt_addr[i] = 0;
		vout->buf_phy_addr[i] = 0;
	}
	vout->buffer_allocated = num_buffers;
}