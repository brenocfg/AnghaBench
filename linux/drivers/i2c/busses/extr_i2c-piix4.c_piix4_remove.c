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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  piix4_adap_remove (int /*<<< orphan*/ *) ; 
 int piix4_adapter_count ; 
 int /*<<< orphan*/ * piix4_aux_adapter ; 
 int /*<<< orphan*/ ** piix4_main_adapters ; 

__attribute__((used)) static void piix4_remove(struct pci_dev *dev)
{
	int port = piix4_adapter_count;

	while (--port >= 0) {
		if (piix4_main_adapters[port]) {
			piix4_adap_remove(piix4_main_adapters[port]);
			piix4_main_adapters[port] = NULL;
		}
	}

	if (piix4_aux_adapter) {
		piix4_adap_remove(piix4_aux_adapter);
		piix4_aux_adapter = NULL;
	}
}