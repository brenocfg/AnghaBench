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
struct TYPE_2__ {int sdma_vm_addr; } ;
struct queue {TYPE_1__ properties; } ;
struct qcm_process_device {int dummy; } ;
struct device_queue_manager {int dummy; } ;

/* Variables and functions */
 int SDMA0_RLC0_VIRTUAL_ADDR__SHARED_BASE_MASK ; 
 int SDMA0_RLC0_VIRTUAL_ADDR__SHARED_BASE__SHIFT ; 
 int get_sh_mem_bases_nybble_64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qpd_to_pdd (struct qcm_process_device*) ; 

__attribute__((used)) static void init_sdma_vm_hawaii(struct device_queue_manager *dqm,
				struct queue *q,
				struct qcm_process_device *qpd)
{
	/* On dGPU we're always in GPUVM64 addressing mode with 64-bit
	 * aperture addresses.
	 */
	q->properties.sdma_vm_addr =
		((get_sh_mem_bases_nybble_64(qpd_to_pdd(qpd))) <<
		 SDMA0_RLC0_VIRTUAL_ADDR__SHARED_BASE__SHIFT) &
		SDMA0_RLC0_VIRTUAL_ADDR__SHARED_BASE_MASK;
}