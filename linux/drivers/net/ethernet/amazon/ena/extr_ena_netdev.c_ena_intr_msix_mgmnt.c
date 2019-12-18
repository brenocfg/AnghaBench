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
struct ena_adapter {int /*<<< orphan*/  ena_dev; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_FLAG_DEVICE_RUNNING ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ena_com_admin_q_comp_intr_handler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_aenq_intr_handler (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ena_intr_msix_mgmnt(int irq, void *data)
{
	struct ena_adapter *adapter = (struct ena_adapter *)data;

	ena_com_admin_q_comp_intr_handler(adapter->ena_dev);

	/* Don't call the aenq handler before probe is done */
	if (likely(test_bit(ENA_FLAG_DEVICE_RUNNING, &adapter->flags)))
		ena_com_aenq_intr_handler(adapter->ena_dev, data);

	return IRQ_HANDLED;
}