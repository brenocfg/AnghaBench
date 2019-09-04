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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int sin; int cos; } ;
struct TYPE_8__ {TYPE_1__ sat; } ;
struct nv50_head_atom {TYPE_2__ procamp; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {int index; TYPE_4__ base; } ;
struct nv50_head {TYPE_5__ base; } ;
struct nv50_dmac {int dummy; } ;
struct TYPE_12__ {TYPE_3__* core; } ;
struct TYPE_9__ {struct nv50_dmac chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  evo_data (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evo_kick (int /*<<< orphan*/ *,struct nv50_dmac*) ; 
 int /*<<< orphan*/  evo_mthd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * evo_wait (struct nv50_dmac*,int) ; 
 TYPE_6__* nv50_disp (int /*<<< orphan*/ ) ; 

void
head507d_procamp(struct nv50_head *head, struct nv50_head_atom *asyh)
{
	struct nv50_dmac *core = &nv50_disp(head->base.base.dev)->core->chan;
	u32 *push;
	if ((push = evo_wait(core, 2))) {
		evo_mthd(push, 0x08a8 + (head->base.index * 0x400), 1);
		evo_data(push, asyh->procamp.sat.sin << 20 |
			       asyh->procamp.sat.cos << 8);
		evo_kick(push, core);
	}
}