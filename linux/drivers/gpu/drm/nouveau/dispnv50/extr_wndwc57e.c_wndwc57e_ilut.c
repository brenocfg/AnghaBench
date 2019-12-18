#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_6__ {int mode; int size; int /*<<< orphan*/  load; scalar_t__ output_mode; } ;
struct TYPE_4__ {TYPE_3__ i; } ;
struct nv50_wndw_atom {TYPE_1__ xlut; TYPE_2__* ilut; } ;
struct nv50_wndw {int dummy; } ;
struct drm_color_lut {int dummy; } ;
struct TYPE_5__ {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  wndwc57e_ilut_load ; 

__attribute__((used)) static void
wndwc57e_ilut(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw)
{
	u16 size = asyw->ilut->length / sizeof(struct drm_color_lut);
	if (size == 256) {
		asyw->xlut.i.mode = 1; /* DIRECT8. */
	} else {
		asyw->xlut.i.mode = 2; /* DIRECT10. */
		size = 1024;
	}
	asyw->xlut.i.size = 4 /* VSS header. */ + size + 1 /* Entries. */;
	asyw->xlut.i.output_mode = 0; /* INTERPOLATE_DISABLE. */
	asyw->xlut.i.load = wndwc57e_ilut_load;
}