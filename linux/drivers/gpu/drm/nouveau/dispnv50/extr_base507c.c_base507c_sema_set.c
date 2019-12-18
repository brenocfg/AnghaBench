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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  release; int /*<<< orphan*/  acquire; int /*<<< orphan*/  offset; } ;
struct nv50_wndw_atom {TYPE_1__ sema; } ;
struct nv50_wndw {int /*<<< orphan*/  wndw; } ;

/* Variables and functions */
 int /*<<< orphan*/  evo_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evo_kick (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evo_mthd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * evo_wait (int /*<<< orphan*/ *,int) ; 

void
base507c_sema_set(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw)
{
	u32 *push;
	if ((push = evo_wait(&wndw->wndw, 5))) {
		evo_mthd(push, 0x0088, 4);
		evo_data(push, asyw->sema.offset);
		evo_data(push, asyw->sema.acquire);
		evo_data(push, asyw->sema.release);
		evo_data(push, asyw->sema.handle);
		evo_kick(push, &wndw->wndw);
	}
}