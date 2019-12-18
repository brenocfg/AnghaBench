#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {int offset; int h; int w; int layout; int pitch; int blocks; int blockh; int format; int handle; int y; int x; } ;
struct nv50_head_atom {TYPE_4__ core; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int index; TYPE_2__ base; } ;
struct nv50_head {TYPE_3__ base; } ;
struct nv50_dmac {int dummy; } ;
struct TYPE_10__ {TYPE_1__* core; } ;
struct TYPE_6__ {struct nv50_dmac chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  evo_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evo_kick (int /*<<< orphan*/ *,struct nv50_dmac*) ; 
 int /*<<< orphan*/  evo_mthd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * evo_wait (struct nv50_dmac*,int) ; 
 TYPE_5__* nv50_disp (int /*<<< orphan*/ ) ; 

void
head907d_core_set(struct nv50_head *head, struct nv50_head_atom *asyh)
{
	struct nv50_dmac *core = &nv50_disp(head->base.base.dev)->core->chan;
	u32 *push;
	if ((push = evo_wait(core, 9))) {
		evo_mthd(push, 0x0460 + head->base.index * 0x300, 1);
		evo_data(push, asyh->core.offset >> 8);
		evo_mthd(push, 0x0468 + head->base.index * 0x300, 4);
		evo_data(push, asyh->core.h << 16 | asyh->core.w);
		evo_data(push, asyh->core.layout << 24 |
			       (asyh->core.pitch >> 8) << 8 |
			       asyh->core.blocks << 8 |
			       asyh->core.blockh);
		evo_data(push, asyh->core.format << 8);
		evo_data(push, asyh->core.handle);
		evo_mthd(push, 0x04b0 + head->base.index * 0x300, 1);
		evo_data(push, asyh->core.y << 16 | asyh->core.x);
		evo_kick(push, core);
	}
}