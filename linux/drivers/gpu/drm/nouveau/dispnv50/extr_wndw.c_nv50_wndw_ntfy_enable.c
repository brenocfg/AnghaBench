#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ntfy; } ;
struct TYPE_12__ {int offset; int awaken; int /*<<< orphan*/  handle; } ;
struct nv50_wndw_atom {TYPE_3__ set; TYPE_6__ ntfy; } ;
struct TYPE_7__ {int /*<<< orphan*/  handle; } ;
struct TYPE_8__ {TYPE_1__ sync; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct nv50_wndw {int ntfy; TYPE_4__* func; TYPE_2__ wndw; TYPE_5__ plane; } ;
struct nv50_disp {int /*<<< orphan*/  sync; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* ntfy_reset ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 struct nv50_disp* nv50_disp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

void
nv50_wndw_ntfy_enable(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw)
{
	struct nv50_disp *disp = nv50_disp(wndw->plane.dev);

	asyw->ntfy.handle = wndw->wndw.sync.handle;
	asyw->ntfy.offset = wndw->ntfy;
	asyw->ntfy.awaken = false;
	asyw->set.ntfy = true;

	wndw->func->ntfy_reset(disp->sync, wndw->ntfy);
	wndw->ntfy ^= 0x10;
}