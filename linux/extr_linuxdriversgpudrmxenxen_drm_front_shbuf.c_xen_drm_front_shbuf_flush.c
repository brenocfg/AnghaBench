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
struct xen_drm_front_shbuf {int dummy; } ;

/* Variables and functions */

void xen_drm_front_shbuf_flush(struct xen_drm_front_shbuf *buf)
{
#if defined(CONFIG_X86)
	drm_clflush_pages(buf->pages, buf->num_pages);
#endif
}