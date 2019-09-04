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
typedef  int u32 ;
struct TYPE_2__ {int data; } ;
struct nv50_wndw {int /*<<< orphan*/  wimm; TYPE_1__ interlock; } ;

/* Variables and functions */
 size_t NV50_DISP_INTERLOCK_WNDW ; 
 int /*<<< orphan*/  evo_data (int*,int) ; 
 int /*<<< orphan*/  evo_kick (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evo_mthd (int*,int,int) ; 
 int* evo_wait (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
wimmc37b_update(struct nv50_wndw *wndw, u32 *interlock)
{
	u32 *push;
	if ((push = evo_wait(&wndw->wimm, 2))) {
		evo_mthd(push, 0x0200, 1);
		if (interlock[NV50_DISP_INTERLOCK_WNDW] & wndw->interlock.data)
			evo_data(push, 0x00000003);
		else
			evo_data(push, 0x00000001);
		evo_kick(push, &wndw->wimm);
	}
}