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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__* matrix; } ;
struct nv50_wndw_atom {TYPE_1__ csc; } ;
struct nv50_wndw {int dummy; } ;
struct drm_color_ctm {int /*<<< orphan*/ * matrix; } ;

/* Variables and functions */
 scalar_t__ csc_drm_to_base (int /*<<< orphan*/ ) ; 

void
base907c_csc(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw,
	     const struct drm_color_ctm *ctm)
{
	int i, j;

	for (j = 0; j < 3; j++) {
		for (i = 0; i < 4; i++) {
			u32 *val = &asyw->csc.matrix[j * 4 + i];
			/* DRM does not support constant offset, while
			 * HW CSC does. Skip it. */
			if (i == 3) {
				*val = 0;
			} else {
				*val = csc_drm_to_base(ctm->matrix[j * 3 + i]);
			}
		}
	}
}