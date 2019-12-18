#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gasket_interrupt_data {int num_interrupts; int msix_configured; int /*<<< orphan*/  num_configured; TYPE_2__* msix_entries; TYPE_1__* pci_dev; int /*<<< orphan*/  name; int /*<<< orphan*/ ** eventfd_ctxs; } ;
struct TYPE_5__ {int entry; scalar_t__ vector; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MSIX_RETRY_COUNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  gasket_msix_interrupt_handler ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int pci_enable_msix_exact (TYPE_1__*,TYPE_2__*,int) ; 
 int request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gasket_interrupt_data*) ; 

__attribute__((used)) static int
gasket_interrupt_msix_init(struct gasket_interrupt_data *interrupt_data)
{
	int ret = 1;
	int i;

	interrupt_data->msix_entries =
		kcalloc(interrupt_data->num_interrupts,
			sizeof(*interrupt_data->msix_entries), GFP_KERNEL);
	if (!interrupt_data->msix_entries)
		return -ENOMEM;

	for (i = 0; i < interrupt_data->num_interrupts; i++) {
		interrupt_data->msix_entries[i].entry = i;
		interrupt_data->msix_entries[i].vector = 0;
		interrupt_data->eventfd_ctxs[i] = NULL;
	}

	/* Retry MSIX_RETRY_COUNT times if not enough IRQs are available. */
	for (i = 0; i < MSIX_RETRY_COUNT && ret > 0; i++)
		ret = pci_enable_msix_exact(interrupt_data->pci_dev,
					    interrupt_data->msix_entries,
					    interrupt_data->num_interrupts);

	if (ret)
		return ret > 0 ? -EBUSY : ret;
	interrupt_data->msix_configured = 1;

	for (i = 0; i < interrupt_data->num_interrupts; i++) {
		ret = request_irq(interrupt_data->msix_entries[i].vector,
				  gasket_msix_interrupt_handler, 0,
				  interrupt_data->name, interrupt_data);

		if (ret) {
			dev_err(&interrupt_data->pci_dev->dev,
				"Cannot get IRQ for interrupt %d, vector %d; "
				"%d\n",
				i, interrupt_data->msix_entries[i].vector, ret);
			return ret;
		}

		interrupt_data->num_configured++;
	}

	return 0;
}