#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mantis_pci {int /*<<< orphan*/  mantis_mmio; int /*<<< orphan*/  mantis_addr; int /*<<< orphan*/  latency; TYPE_3__* pdev; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  revision; TYPE_1__* hwconfig; } ;
struct TYPE_6__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  devfn; TYPE_2__* bus; } ;
struct TYPE_5__ {int /*<<< orphan*/  number; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_type; int /*<<< orphan*/  model_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_DEBUG ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int get_mac_address (struct mantis_pci*) ; 
 int mantis_dma_init (struct mantis_pci*) ; 
 int mantis_dvb_init (struct mantis_pci*) ; 
 int mantis_i2c_init (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_load_config (struct mantis_pci*) ; 
 int mantis_uart_init (struct mantis_pci*) ; 
 int /*<<< orphan*/  verbose ; 

int mantis_core_init(struct mantis_pci *mantis)
{
	int err = 0;

	mantis_load_config(mantis);
	dprintk(verbose, MANTIS_ERROR, 0, "found a %s PCI %s device on (%02x:%02x.%x),\n",
		mantis->hwconfig->model_name, mantis->hwconfig->dev_type,
		mantis->pdev->bus->number, PCI_SLOT(mantis->pdev->devfn), PCI_FUNC(mantis->pdev->devfn));
	dprintk(verbose, MANTIS_ERROR, 0, "    Mantis Rev %d [%04x:%04x], ",
		mantis->revision,
		mantis->subsystem_vendor, mantis->subsystem_device);
	dprintk(verbose, MANTIS_ERROR, 0,
		"irq: %d, latency: %d\n    memory: 0x%lx, mmio: 0x%p\n",
		mantis->pdev->irq, mantis->latency,
		mantis->mantis_addr, mantis->mantis_mmio);

	err = mantis_i2c_init(mantis);
	if (err < 0) {
		dprintk(verbose, MANTIS_ERROR, 1, "Mantis I2C init failed");
		return err;
	}
	err = get_mac_address(mantis);
	if (err < 0) {
		dprintk(verbose, MANTIS_ERROR, 1, "get MAC address failed");
		return err;
	}
	err = mantis_dma_init(mantis);
	if (err < 0) {
		dprintk(verbose, MANTIS_ERROR, 1, "Mantis DMA init failed");
		return err;
	}
	err = mantis_dvb_init(mantis);
	if (err < 0) {
		dprintk(verbose, MANTIS_DEBUG, 1, "Mantis DVB init failed");
		return err;
	}
	err = mantis_uart_init(mantis);
	if (err < 0) {
		dprintk(verbose, MANTIS_DEBUG, 1, "Mantis UART init failed");
		return err;
	}

	return 0;
}