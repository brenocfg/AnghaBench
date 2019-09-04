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
struct nvkm_instmem {int dummy; } ;
struct TYPE_2__ {unsigned long long addr; } ;

/* Variables and functions */
 TYPE_1__* nv50_instmem (struct nvkm_instmem*) ; 

__attribute__((used)) static void
nv50_instmem_fini(struct nvkm_instmem *base)
{
	nv50_instmem(base)->addr = ~0ULL;
}