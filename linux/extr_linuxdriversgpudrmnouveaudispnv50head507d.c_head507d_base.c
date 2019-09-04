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
typedef  int u32 ;
struct TYPE_6__ {int cpp; } ;
struct nv50_head_atom {TYPE_1__ base; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int index; TYPE_4__ base; } ;
struct nv50_head {TYPE_3__ base; } ;
struct nv50_dmac {int dummy; } ;
struct TYPE_10__ {TYPE_2__* core; } ;
struct TYPE_7__ {struct nv50_dmac chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  evo_data (int*,int) ; 
 int /*<<< orphan*/  evo_kick (int*,struct nv50_dmac*) ; 
 int /*<<< orphan*/  evo_mthd (int*,int,int) ; 
 int* evo_wait (struct nv50_dmac*,int) ; 
 TYPE_5__* nv50_disp (int /*<<< orphan*/ ) ; 

void
head507d_base(struct nv50_head *head, struct nv50_head_atom *asyh)
{
	struct nv50_dmac *core = &nv50_disp(head->base.base.dev)->core->chan;
	u32 bounds = 0;
	u32 *push;

	if (asyh->base.cpp) {
		switch (asyh->base.cpp) {
		case 8: bounds |= 0x00000500; break;
		case 4: bounds |= 0x00000300; break;
		case 2: bounds |= 0x00000100; break;
		case 1: bounds |= 0x00000000; break;
		default:
			WARN_ON(1);
			break;
		}
		bounds |= 0x00000001;
	}

	if ((push = evo_wait(core, 2))) {
		evo_mthd(push, 0x0900 + head->base.index * 0x400, 1);
		evo_data(push, bounds);
		evo_kick(push, core);
	}
}