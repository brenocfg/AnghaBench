#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ flags; int /*<<< orphan*/ * info; int /*<<< orphan*/  func; } ;
struct octeon_droq {int cpu_id; int /*<<< orphan*/  napi; TYPE_1__ csd; struct octeon_device* oct_dev; } ;
struct octeon_device {int dummy; } ;
typedef  TYPE_1__ call_single_data_t ;

/* Variables and functions */
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN23XX_VF (struct octeon_device*) ; 
 int /*<<< orphan*/  napi_schedule_irqoff (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule_wrapper ; 
 int /*<<< orphan*/  smp_call_function_single_async (int,TYPE_1__*) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void liquidio_napi_drv_callback(void *arg)
{
	struct octeon_device *oct;
	struct octeon_droq *droq = arg;
	int this_cpu = smp_processor_id();

	oct = droq->oct_dev;

	if (OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct) ||
	    droq->cpu_id == this_cpu) {
		napi_schedule_irqoff(&droq->napi);
	} else {
		call_single_data_t *csd = &droq->csd;

		csd->func = napi_schedule_wrapper;
		csd->info = &droq->napi;
		csd->flags = 0;

		smp_call_function_single_async(droq->cpu_id, csd);
	}
}