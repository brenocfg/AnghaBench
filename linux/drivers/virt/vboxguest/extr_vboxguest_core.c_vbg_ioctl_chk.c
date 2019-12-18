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
struct vbg_ioctl_hdr {int size_in; int size_out; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int vbg_ioctl_chk(struct vbg_ioctl_hdr *hdr, size_t in_size,
			 size_t out_size)
{
	if (hdr->size_in  != (sizeof(*hdr) + in_size) ||
	    hdr->size_out != (sizeof(*hdr) + out_size))
		return -EINVAL;

	return 0;
}