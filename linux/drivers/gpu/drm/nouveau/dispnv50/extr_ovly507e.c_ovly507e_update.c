#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct nv50_wndw {int /*<<< orphan*/  wndw; } ;

/* Variables and functions */
 size_t NV50_DISP_INTERLOCK_CORE ; 
 int /*<<< orphan*/  evo_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evo_kick (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evo_mthd (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * evo_wait (int /*<<< orphan*/ *,int) ; 

void
ovly507e_update(struct nv50_wndw *wndw, u32 *interlock)
{
	u32 *push;
	if ((push = evo_wait(&wndw->wndw, 2))) {
		evo_mthd(push, 0x0080, 1);
		evo_data(push, interlock[NV50_DISP_INTERLOCK_CORE]);
		evo_kick(push, &wndw->wndw);
	}
}