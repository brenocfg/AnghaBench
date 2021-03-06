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
struct TYPE_9__ {int layout; int format; int handle; int offset; } ;
struct nv50_head_atom {TYPE_4__ curs; } ;
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
headc37d_curs_set(struct nv50_head *head, struct nv50_head_atom *asyh)
{
	struct nv50_dmac *core = &nv50_disp(head->base.base.dev)->core->chan;
	u32 *push;
	if ((push = evo_wait(core, 7))) {
		evo_mthd(push, 0x209c + head->base.index * 0x400, 2);
		evo_data(push, 0x80000000 |
			       asyh->curs.layout << 8 |
			       asyh->curs.format << 0);
		evo_data(push, 0x000072ff);
		evo_mthd(push, 0x2088 + head->base.index * 0x400, 1);
		evo_data(push, asyh->curs.handle);
		evo_mthd(push, 0x2090 + head->base.index * 0x400, 1);
		evo_data(push, asyh->curs.offset >> 8);
		evo_kick(push, core);
	}
}