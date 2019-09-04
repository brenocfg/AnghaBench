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
struct device_queue_manager_asic_ops {int /*<<< orphan*/  init_sdma_vm; int /*<<< orphan*/  update_qpd; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_sdma_vm_v9 ; 
 int /*<<< orphan*/  update_qpd_v9 ; 

void device_queue_manager_init_v9(
	struct device_queue_manager_asic_ops *asic_ops)
{
	asic_ops->update_qpd = update_qpd_v9;
	asic_ops->init_sdma_vm = init_sdma_vm_v9;
}