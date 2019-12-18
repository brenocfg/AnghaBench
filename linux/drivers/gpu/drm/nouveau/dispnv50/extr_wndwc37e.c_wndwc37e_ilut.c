#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mode; int output_mode; int /*<<< orphan*/  load; scalar_t__ range; scalar_t__ size; } ;
struct TYPE_3__ {TYPE_2__ i; } ;
struct nv50_wndw_atom {TYPE_1__ xlut; } ;
struct nv50_wndw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  head907d_olut_load ; 

__attribute__((used)) static void
wndwc37e_ilut(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw)
{
	asyw->xlut.i.mode = 2;
	asyw->xlut.i.size = 0;
	asyw->xlut.i.range = 0;
	asyw->xlut.i.output_mode = 1;
	asyw->xlut.i.load = head907d_olut_load;
}