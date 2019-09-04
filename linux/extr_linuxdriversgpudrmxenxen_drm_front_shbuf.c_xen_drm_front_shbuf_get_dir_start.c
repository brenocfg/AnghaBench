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
struct xen_drm_front_shbuf {int /*<<< orphan*/ * grefs; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRANT_INVALID_REF ; 

grant_ref_t xen_drm_front_shbuf_get_dir_start(struct xen_drm_front_shbuf *buf)
{
	if (!buf->grefs)
		return GRANT_INVALID_REF;

	return buf->grefs[0];
}