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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct nvkm_gr {TYPE_2__ engine; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvkm_rd32 (int /*<<< orphan*/ ,int) ; 

u64
nv40_gr_units(struct nvkm_gr *gr)
{
	return nvkm_rd32(gr->engine.subdev.device, 0x1540);
}