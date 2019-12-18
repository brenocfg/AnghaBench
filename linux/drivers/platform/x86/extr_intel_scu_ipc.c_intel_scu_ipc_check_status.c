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
struct intel_scu_ipc_dev {scalar_t__ irq_mode; } ;

/* Variables and functions */
 int busy_loop (struct intel_scu_ipc_dev*) ; 
 int ipc_wait_for_interrupt (struct intel_scu_ipc_dev*) ; 

__attribute__((used)) static int intel_scu_ipc_check_status(struct intel_scu_ipc_dev *scu)
{
	return scu->irq_mode ? ipc_wait_for_interrupt(scu) : busy_loop(scu);
}