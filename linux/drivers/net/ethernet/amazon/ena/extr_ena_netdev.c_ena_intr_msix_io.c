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
struct ena_napi {int /*<<< orphan*/  napi; TYPE_2__* rx_ring; TYPE_1__* tx_ring; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int first_interrupt; } ;
struct TYPE_3__ {int first_interrupt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  napi_schedule_irqoff (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ena_intr_msix_io(int irq, void *data)
{
	struct ena_napi *ena_napi = data;

	ena_napi->tx_ring->first_interrupt = true;
	ena_napi->rx_ring->first_interrupt = true;

	napi_schedule_irqoff(&ena_napi->napi);

	return IRQ_HANDLED;
}