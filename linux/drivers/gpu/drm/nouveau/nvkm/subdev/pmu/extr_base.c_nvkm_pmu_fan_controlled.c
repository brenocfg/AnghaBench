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
struct nvkm_pmu {TYPE_2__* func; } ;
struct nvkm_device {int chipset; struct nvkm_pmu* pmu; } ;
struct TYPE_3__ {scalar_t__ size; } ;
struct TYPE_4__ {TYPE_1__ code; } ;

/* Variables and functions */

bool
nvkm_pmu_fan_controlled(struct nvkm_device *device)
{
	struct nvkm_pmu *pmu = device->pmu;

	/* Internal PMU FW does not currently control fans in any way,
	 * allow SW control of fans instead.
	 */
	if (pmu && pmu->func->code.size)
		return false;

	/* Default (board-loaded, or VBIOS PMU/PREOS) PMU FW on Fermi
	 * and newer automatically control the fan speed, which would
	 * interfere with SW control.
	 */
	return (device->chipset >= 0xc0);
}