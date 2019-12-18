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
struct TYPE_2__ {int depth; int k1; int dst_color; int src_color; } ;
struct nv50_wndw_atom {TYPE_1__ blend; } ;
struct nv50_wndw {int /*<<< orphan*/  wndw; } ;

/* Variables and functions */
 int /*<<< orphan*/  evo_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evo_kick (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evo_mthd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * evo_wait (int /*<<< orphan*/ *,int) ; 

void
wndwc37e_blend_set(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw)
{
	u32 *push;
	if ((push = evo_wait(&wndw->wndw, 8))) {
		evo_mthd(push, 0x02ec, 7);
		evo_data(push, asyw->blend.depth << 4);
		evo_data(push, asyw->blend.k1);
		evo_data(push, asyw->blend.dst_color << 12 |
			       asyw->blend.dst_color << 8 |
			       asyw->blend.src_color << 4 |
			       asyw->blend.src_color);
		evo_data(push, 0xffff0000);
		evo_data(push, 0xffff0000);
		evo_data(push, 0xffff0000);
		evo_data(push, 0xffff0000);
		evo_kick(push, &wndw->wndw);
	}
}