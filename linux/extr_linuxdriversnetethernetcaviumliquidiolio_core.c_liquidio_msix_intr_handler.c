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
typedef  int u64 ;
struct octeon_ioq_vector {size_t droq_index; struct octeon_device* oct_dev; } ;
struct octeon_droq {int dummy; } ;
struct TYPE_2__ {int (* msix_interrupt_handler ) (struct octeon_ioq_vector*) ;} ;
struct octeon_device {TYPE_1__ fn_list; struct octeon_droq** droq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MSIX_PI_INT ; 
 int MSIX_PO_INT ; 
 int /*<<< orphan*/  liquidio_schedule_msix_droq_pkt_handler (struct octeon_droq*,int) ; 
 int stub1 (struct octeon_ioq_vector*) ; 

irqreturn_t
liquidio_msix_intr_handler(int irq __attribute__((unused)), void *dev)
{
	struct octeon_ioq_vector *ioq_vector = (struct octeon_ioq_vector *)dev;
	struct octeon_device *oct = ioq_vector->oct_dev;
	struct octeon_droq *droq = oct->droq[ioq_vector->droq_index];
	u64 ret;

	ret = oct->fn_list.msix_interrupt_handler(ioq_vector);

	if (ret & MSIX_PO_INT || ret & MSIX_PI_INT)
		liquidio_schedule_msix_droq_pkt_handler(droq, ret);

	return IRQ_HANDLED;
}