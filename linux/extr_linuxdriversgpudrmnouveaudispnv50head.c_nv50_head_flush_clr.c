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
union nv50_head_atom_mask {int mask; scalar_t__ curs; scalar_t__ core; scalar_t__ olut; } ;
struct TYPE_5__ {int mask; } ;
struct TYPE_4__ {int mask; } ;
struct nv50_head_atom {TYPE_2__ set; TYPE_1__ clr; } ;
struct nv50_head {TYPE_3__* func; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* curs_clr ) (struct nv50_head*) ;int /*<<< orphan*/  (* core_clr ) (struct nv50_head*) ;int /*<<< orphan*/  (* olut_clr ) (struct nv50_head*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nv50_head*) ; 
 int /*<<< orphan*/  stub2 (struct nv50_head*) ; 
 int /*<<< orphan*/  stub3 (struct nv50_head*) ; 

void
nv50_head_flush_clr(struct nv50_head *head,
		    struct nv50_head_atom *asyh, bool flush)
{
	union nv50_head_atom_mask clr = {
		.mask = asyh->clr.mask & ~(flush ? 0 : asyh->set.mask),
	};
	if (clr.olut) head->func->olut_clr(head);
	if (clr.core) head->func->core_clr(head);
	if (clr.curs) head->func->curs_clr(head);
}