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
struct service_processor {int /*<<< orphan*/  base_address; int /*<<< orphan*/  irq; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYSTEM_STATE_OS_DOWN ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  disable_sp_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ibmasm_event_buffer_exit (struct service_processor*) ; 
 int /*<<< orphan*/  ibmasm_free_remote_input_dev (struct service_processor*) ; 
 int /*<<< orphan*/  ibmasm_heartbeat_exit (struct service_processor*) ; 
 scalar_t__ ibmasm_send_os_state (struct service_processor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmasm_unregister_uart (struct service_processor*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct service_processor*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct service_processor* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 

__attribute__((used)) static void ibmasm_remove_one(struct pci_dev *pdev)
{
	struct service_processor *sp = pci_get_drvdata(pdev);

	dbg("Unregistering UART\n");
	ibmasm_unregister_uart(sp);
	dbg("Sending OS down message\n");
	if (ibmasm_send_os_state(sp, SYSTEM_STATE_OS_DOWN))
		err("failed to get response to 'Send OS State' command\n");
	dbg("Disabling heartbeats\n");
	ibmasm_heartbeat_exit(sp);
	dbg("Disabling interrupts\n");
	disable_sp_interrupts(sp->base_address);
	dbg("Freeing SP irq\n");
	free_irq(sp->irq, (void *)sp);
	dbg("Cleaning up\n");
	ibmasm_free_remote_input_dev(sp);
	iounmap(sp->base_address);
	ibmasm_event_buffer_exit(sp);
	kfree(sp);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
}