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
struct nvkm_vmm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gf100_vmm_flush_ (struct nvkm_vmm*,int) ; 

void
gp100_vmm_flush(struct nvkm_vmm *vmm, int depth)
{
	gf100_vmm_flush_(vmm, 5 /* CACHE_LEVEL_UP_TO_PDE3 */ - depth);
}