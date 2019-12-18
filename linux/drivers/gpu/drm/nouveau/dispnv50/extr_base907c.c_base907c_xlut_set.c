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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int enable; int mode; int offset; } ;
struct TYPE_4__ {int handle; TYPE_1__ i; } ;
struct nv50_wndw_atom {TYPE_2__ xlut; } ;
struct nv50_wndw {int /*<<< orphan*/  wndw; } ;

/* Variables and functions */
 int /*<<< orphan*/  evo_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evo_kick (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evo_mthd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * evo_wait (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
base907c_xlut_set(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw)
{
	u32 *push;
	if ((push = evo_wait(&wndw->wndw, 6))) {
		evo_mthd(push, 0x00e0, 3);
		evo_data(push, asyw->xlut.i.enable << 30 |
			       asyw->xlut.i.mode << 24);
		evo_data(push, asyw->xlut.i.offset >> 8);
		evo_data(push, 0x40000000);
		evo_mthd(push, 0x00fc, 1);
		evo_data(push, asyw->xlut.handle);
		evo_kick(push, &wndw->wndw);
	}
}