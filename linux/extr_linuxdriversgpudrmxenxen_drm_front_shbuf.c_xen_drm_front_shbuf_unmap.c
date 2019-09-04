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
struct xen_drm_front_shbuf {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* unmap ) (struct xen_drm_front_shbuf*) ;} ;

/* Variables and functions */
 int stub1 (struct xen_drm_front_shbuf*) ; 

int xen_drm_front_shbuf_unmap(struct xen_drm_front_shbuf *buf)
{
	if (buf->ops->unmap)
		return buf->ops->unmap(buf);

	/* no need to unmap own grant references */
	return 0;
}