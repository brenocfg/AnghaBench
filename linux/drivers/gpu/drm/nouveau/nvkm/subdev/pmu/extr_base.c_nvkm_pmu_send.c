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
typedef  int /*<<< orphan*/  u32 ;
struct nvkm_pmu {TYPE_1__* func; } ;
struct TYPE_2__ {int (* send ) (struct nvkm_pmu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (struct nvkm_pmu*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
nvkm_pmu_send(struct nvkm_pmu *pmu, u32 reply[2],
	      u32 process, u32 message, u32 data0, u32 data1)
{
	if (!pmu || !pmu->func->send)
		return -ENODEV;
	return pmu->func->send(pmu, reply, process, message, data0, data1);
}