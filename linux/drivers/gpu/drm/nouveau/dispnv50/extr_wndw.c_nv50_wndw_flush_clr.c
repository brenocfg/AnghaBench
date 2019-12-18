#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union nv50_wndw_atom_mask {int mask; scalar_t__ image; scalar_t__ csc; scalar_t__ xlut; scalar_t__ ntfy; scalar_t__ sema; } ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int mask; } ;
struct TYPE_5__ {int mask; } ;
struct nv50_wndw_atom {TYPE_2__ set; TYPE_1__ clr; } ;
struct TYPE_8__ {size_t type; int /*<<< orphan*/  data; } ;
struct nv50_wndw {TYPE_4__ interlock; TYPE_3__* func; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* image_clr ) (struct nv50_wndw*) ;int /*<<< orphan*/  (* csc_clr ) (struct nv50_wndw*) ;int /*<<< orphan*/  (* xlut_clr ) (struct nv50_wndw*) ;int /*<<< orphan*/  (* ntfy_clr ) (struct nv50_wndw*) ;int /*<<< orphan*/  (* sema_clr ) (struct nv50_wndw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct nv50_wndw*) ; 
 int /*<<< orphan*/  stub2 (struct nv50_wndw*) ; 
 int /*<<< orphan*/  stub3 (struct nv50_wndw*) ; 
 int /*<<< orphan*/  stub4 (struct nv50_wndw*) ; 
 int /*<<< orphan*/  stub5 (struct nv50_wndw*) ; 

void
nv50_wndw_flush_clr(struct nv50_wndw *wndw, u32 *interlock, bool flush,
		    struct nv50_wndw_atom *asyw)
{
	union nv50_wndw_atom_mask clr = {
		.mask = asyw->clr.mask & ~(flush ? 0 : asyw->set.mask),
	};
	if (clr.sema ) wndw->func-> sema_clr(wndw);
	if (clr.ntfy ) wndw->func-> ntfy_clr(wndw);
	if (clr.xlut ) wndw->func-> xlut_clr(wndw);
	if (clr.csc  ) wndw->func->  csc_clr(wndw);
	if (clr.image) wndw->func->image_clr(wndw);

	interlock[wndw->interlock.type] |= wndw->interlock.data;
}