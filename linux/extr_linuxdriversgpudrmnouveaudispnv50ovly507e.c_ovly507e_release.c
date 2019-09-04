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
struct TYPE_2__ {scalar_t__ cpp; } ;
struct nv50_head_atom {TYPE_1__ ovly; } ;

/* Variables and functions */

void
ovly507e_release(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw,
		 struct nv50_head_atom *asyh)
{
	asyh->ovly.cpp = 0;
}