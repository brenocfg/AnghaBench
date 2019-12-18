#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int format; } ;
struct nv50_wndw_atom {TYPE_1__ image; } ;
struct TYPE_4__ {int format; } ;
struct nv50_head_atom {TYPE_2__ curs; } ;
struct nv50_head {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

int
head507d_curs_format(struct nv50_head *head, struct nv50_wndw_atom *asyw,
		     struct nv50_head_atom *asyh)
{
	switch (asyw->image.format) {
	case 0xcf: asyh->curs.format = 1; break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}
	return 0;
}