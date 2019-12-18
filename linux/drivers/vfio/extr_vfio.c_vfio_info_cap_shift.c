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
struct vfio_info_cap_header {int next; } ;
struct vfio_info_cap {scalar_t__ buf; } ;

/* Variables and functions */

void vfio_info_cap_shift(struct vfio_info_cap *caps, size_t offset)
{
	struct vfio_info_cap_header *tmp;
	void *buf = (void *)caps->buf;

	for (tmp = buf; tmp->next; tmp = buf + tmp->next - offset)
		tmp->next += offset;
}