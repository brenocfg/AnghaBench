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
struct TYPE_2__ {int /*<<< orphan*/ * matrix; } ;
struct nv50_wndw_atom {TYPE_1__ csc; } ;
struct nv50_wndw {int /*<<< orphan*/  wndw; } ;

/* Variables and functions */
 int /*<<< orphan*/  evo_data (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evo_kick (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evo_mthd (int*,int,int) ; 
 int* evo_wait (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
wndwc37e_csc_set(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw)
{
	u32 *push, i;
	if ((push = evo_wait(&wndw->wndw, 13))) {
		 evo_mthd(push, 0x02bc, 12);
		 for (i = 0; i < 12; i++)
			  evo_data(push, asyw->csc.matrix[i]);
		 evo_kick(push, &wndw->wndw);
	}
}