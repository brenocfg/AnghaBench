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
struct TYPE_5__ {TYPE_1__* fb; } ;
struct nv50_wndw_atom {TYPE_2__ state; } ;
struct TYPE_6__ {int layout; } ;
struct nv50_head_atom {TYPE_3__ curs; } ;
struct nv50_head {int dummy; } ;
struct TYPE_4__ {int width; } ;

/* Variables and functions */
 int EINVAL ; 

int
head917d_curs_layout(struct nv50_head *head, struct nv50_wndw_atom *asyw,
		     struct nv50_head_atom *asyh)
{
	switch (asyw->state.fb->width) {
	case  32: asyh->curs.layout = 0; break;
	case  64: asyh->curs.layout = 1; break;
	case 128: asyh->curs.layout = 2; break;
	case 256: asyh->curs.layout = 3; break;
	default:
		return -EINVAL;
	}
	return 0;
}