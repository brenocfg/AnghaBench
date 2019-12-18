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
struct xdp_frame {int dummy; } ;

/* Variables and functions */
 unsigned long VIRTIO_XDP_FLAG ; 

__attribute__((used)) static struct xdp_frame *ptr_to_xdp(void *ptr)
{
	return (struct xdp_frame *)((unsigned long)ptr & ~VIRTIO_XDP_FLAG);
}