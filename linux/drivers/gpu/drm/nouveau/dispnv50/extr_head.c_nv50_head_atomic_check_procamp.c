#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int procamp; } ;
struct TYPE_5__ {int cos; int sin; } ;
struct TYPE_6__ {TYPE_1__ sat; } ;
struct nv50_head_atom {TYPE_3__ set; TYPE_2__ procamp; } ;
struct TYPE_8__ {int color_vibrance; int vibrant_hue; } ;
struct nouveau_conn_atom {TYPE_4__ procamp; } ;

/* Variables and functions */

__attribute__((used)) static void
nv50_head_atomic_check_procamp(struct nv50_head_atom *armh,
			       struct nv50_head_atom *asyh,
			       struct nouveau_conn_atom *asyc)
{
	const int vib = asyc->procamp.color_vibrance - 100;
	const int hue = asyc->procamp.vibrant_hue - 90;
	const int adj = (vib > 0) ? 50 : 0;
	asyh->procamp.sat.cos = ((vib * 2047 + adj) / 100) & 0xfff;
	asyh->procamp.sat.sin = ((hue * 2047) / 100) & 0xfff;
	asyh->set.procamp = true;
}