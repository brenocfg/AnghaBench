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
typedef  scalar_t__ u32 ;
struct nvkm_instmem {int dummy; } ;
struct TYPE_2__ {scalar_t__ iomem; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32_native (scalar_t__,scalar_t__) ; 
 TYPE_1__* nv40_instmem (struct nvkm_instmem*) ; 

__attribute__((used)) static void
nv40_instmem_wr32(struct nvkm_instmem *base, u32 addr, u32 data)
{
	iowrite32_native(data, nv40_instmem(base)->iomem + addr);
}