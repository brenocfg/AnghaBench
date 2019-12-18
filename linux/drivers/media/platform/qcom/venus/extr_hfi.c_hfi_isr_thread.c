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
struct venus_core {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* isr_thread ) (struct venus_core*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct venus_core*) ; 

irqreturn_t hfi_isr_thread(int irq, void *dev_id)
{
	struct venus_core *core = dev_id;

	return core->ops->isr_thread(core);
}