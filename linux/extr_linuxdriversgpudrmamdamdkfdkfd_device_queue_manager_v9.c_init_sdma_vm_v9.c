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
struct TYPE_2__ {scalar_t__ sdma_vm_addr; } ;
struct queue {TYPE_1__ properties; } ;
struct qcm_process_device {int dummy; } ;
struct device_queue_manager {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void init_sdma_vm_v9(struct device_queue_manager *dqm, struct queue *q,
			    struct qcm_process_device *qpd)
{
	/* Not needed on SDMAv4 any more */
	q->properties.sdma_vm_addr = 0;
}