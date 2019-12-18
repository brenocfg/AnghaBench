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
typedef  int u64 ;
typedef  int u32 ;
struct nvkm_gr {int dummy; } ;
struct gf100_gr {scalar_t__ rop_nr; scalar_t__ tpc_total; scalar_t__ gpc_nr; } ;

/* Variables and functions */
 struct gf100_gr* gf100_gr (struct nvkm_gr*) ; 

u64
gf100_gr_units(struct nvkm_gr *base)
{
	struct gf100_gr *gr = gf100_gr(base);
	u64 cfg;

	cfg  = (u32)gr->gpc_nr;
	cfg |= (u32)gr->tpc_total << 8;
	cfg |= (u64)gr->rop_nr << 32;

	return cfg;
}