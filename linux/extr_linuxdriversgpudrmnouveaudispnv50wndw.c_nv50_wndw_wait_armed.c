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
struct TYPE_10__ {int /*<<< orphan*/  offset; } ;
struct TYPE_8__ {scalar_t__ ntfy; } ;
struct nv50_wndw_atom {TYPE_4__ ntfy; TYPE_2__ set; } ;
struct TYPE_11__ {int /*<<< orphan*/  device; } ;
struct TYPE_12__ {TYPE_5__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct nv50_wndw {TYPE_6__ wndw; TYPE_3__* func; TYPE_1__ plane; } ;
struct nv50_disp {int /*<<< orphan*/  sync; } ;
struct TYPE_9__ {int (* ntfy_wait_begun ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct nv50_disp* nv50_disp (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nv50_wndw_wait_armed(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw)
{
	struct nv50_disp *disp = nv50_disp(wndw->plane.dev);
	if (asyw->set.ntfy) {
		return wndw->func->ntfy_wait_begun(disp->sync,
						   asyw->ntfy.offset,
						   wndw->wndw.base.device);
	}
	return 0;
}