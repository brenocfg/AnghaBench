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
struct TYPE_6__ {int mode; int size; int output_mode; int /*<<< orphan*/  load; } ;
struct TYPE_5__ {TYPE_1__* gamma_lut; } ;
struct nv50_head_atom {TYPE_3__ olut; TYPE_2__ state; } ;
struct nv50_head {int dummy; } ;
struct drm_color_lut {int dummy; } ;
struct TYPE_4__ {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  headc57d_olut_load ; 
 int /*<<< orphan*/  headc57d_olut_load_8 ; 

void
headc57d_olut(struct nv50_head *head, struct nv50_head_atom *asyh)
{
	asyh->olut.mode = 2; /* DIRECT10 */
	asyh->olut.size = 4 /* VSS header. */ + 1024 + 1 /* Entries. */;
	asyh->olut.output_mode = 1; /* INTERPOLATE_ENABLE. */
	if (asyh->state.gamma_lut &&
	    asyh->state.gamma_lut->length / sizeof(struct drm_color_lut) == 256)
		asyh->olut.load = headc57d_olut_load_8;
	else
		asyh->olut.load = headc57d_olut_load;
}