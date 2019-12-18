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
struct pcie_pme_service_data {int /*<<< orphan*/  work; } ;
struct pcie_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pcie_device*) ; 
 struct pcie_pme_service_data* get_service_data (struct pcie_device*) ; 
 int /*<<< orphan*/  kfree (struct pcie_pme_service_data*) ; 
 int /*<<< orphan*/  pcie_pme_disable_interrupt (int /*<<< orphan*/ ,struct pcie_pme_service_data*) ; 

__attribute__((used)) static void pcie_pme_remove(struct pcie_device *srv)
{
	struct pcie_pme_service_data *data = get_service_data(srv);

	pcie_pme_disable_interrupt(srv->port, data);
	free_irq(srv->irq, srv);
	cancel_work_sync(&data->work);
	kfree(data);
}