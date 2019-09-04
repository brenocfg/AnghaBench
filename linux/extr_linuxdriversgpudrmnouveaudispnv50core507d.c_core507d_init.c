#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
struct TYPE_5__ {TYPE_1__ sync; } ;
struct nv50_core {TYPE_2__ chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  evo_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evo_kick (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  evo_mthd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * evo_wait (TYPE_2__*,int) ; 

void
core507d_init(struct nv50_core *core)
{
	u32 *push;
	if ((push = evo_wait(&core->chan, 2))) {
		evo_mthd(push, 0x0088, 1);
		evo_data(push, core->chan.sync.handle);
		evo_kick(push, &core->chan);
	}
}