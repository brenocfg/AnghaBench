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
typedef  int u32 ;
struct TYPE_4__ {int handle; } ;
struct TYPE_5__ {TYPE_1__ sync; } ;
struct nv50_core {TYPE_2__ chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  evo_data (int*,int) ; 
 int /*<<< orphan*/  evo_kick (int*,TYPE_2__*) ; 
 int /*<<< orphan*/  evo_mthd (int*,int,int) ; 
 int* evo_wait (TYPE_2__*,int) ; 

__attribute__((used)) static void
corec37d_init(struct nv50_core *core)
{
	const u32 windows = 8; /*XXX*/
	u32 *push, i;
	if ((push = evo_wait(&core->chan, 2 + 6 * windows + 2))) {
		evo_mthd(push, 0x0208, 1);
		evo_data(push, core->chan.sync.handle);
		for (i = 0; i < windows; i++) {
			evo_mthd(push, 0x1000 + (i * 0x080), 3);
			evo_data(push, i >> 1);
			evo_data(push, 0x0000001f);
			evo_data(push, 0x00000000);
			evo_mthd(push, 0x1010 + (i * 0x080), 1);
			evo_data(push, 0x00127fff);
		}
		evo_mthd(push, 0x0200, 1);
		evo_data(push, 0x00000001);
		evo_kick(push, &core->chan);
	}
}