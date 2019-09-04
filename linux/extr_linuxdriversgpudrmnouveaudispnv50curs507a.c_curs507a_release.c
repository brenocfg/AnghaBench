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
struct nv50_wndw_atom {int dummy; } ;
struct nv50_wndw {int dummy; } ;
struct TYPE_2__ {int visible; } ;
struct nv50_head_atom {TYPE_1__ curs; } ;

/* Variables and functions */

__attribute__((used)) static void
curs507a_release(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw,
		 struct nv50_head_atom *asyh)
{
	asyh->curs.visible = false;
}