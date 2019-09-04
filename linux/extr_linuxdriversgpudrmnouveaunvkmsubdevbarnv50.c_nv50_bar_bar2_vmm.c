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
struct nvkm_vmm {int dummy; } ;
struct nvkm_bar {int dummy; } ;
struct TYPE_2__ {struct nvkm_vmm* bar2_vmm; } ;

/* Variables and functions */
 TYPE_1__* nv50_bar (struct nvkm_bar*) ; 

struct nvkm_vmm *
nv50_bar_bar2_vmm(struct nvkm_bar *base)
{
	return nv50_bar(base)->bar2_vmm;
}