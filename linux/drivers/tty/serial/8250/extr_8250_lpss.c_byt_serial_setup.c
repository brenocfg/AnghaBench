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
struct uart_port {scalar_t__ membase; int /*<<< orphan*/  get_mctrl; int /*<<< orphan*/  set_termios; int /*<<< orphan*/  dev; } ;
struct pci_dev {int device; int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; int /*<<< orphan*/  devfn; } ;
struct dw_dma_slave {int src_id; int dst_id; int p_master; scalar_t__ m_master; int /*<<< orphan*/ * dma_dev; } ;
struct lpss8250 {int dma_maxburst; struct dw_dma_slave dma_param; } ;

/* Variables and functions */
 scalar_t__ BYT_TX_OVF_INT ; 
 int /*<<< orphan*/  BYT_TX_OVF_INT_MASK ; 
 int EINVAL ; 
 unsigned int PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PCI_DEVICE_ID_INTEL_BDW_UART1 133 
#define  PCI_DEVICE_ID_INTEL_BDW_UART2 132 
#define  PCI_DEVICE_ID_INTEL_BSW_UART1 131 
#define  PCI_DEVICE_ID_INTEL_BSW_UART2 130 
#define  PCI_DEVICE_ID_INTEL_BYT_UART1 129 
#define  PCI_DEVICE_ID_INTEL_BYT_UART2 128 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  byt_get_mctrl ; 
 int /*<<< orphan*/  byt_set_termios ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,unsigned int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int byt_serial_setup(struct lpss8250 *lpss, struct uart_port *port)
{
	struct dw_dma_slave *param = &lpss->dma_param;
	struct pci_dev *pdev = to_pci_dev(port->dev);
	unsigned int dma_devfn = PCI_DEVFN(PCI_SLOT(pdev->devfn), 0);
	struct pci_dev *dma_dev = pci_get_slot(pdev->bus, dma_devfn);

	switch (pdev->device) {
	case PCI_DEVICE_ID_INTEL_BYT_UART1:
	case PCI_DEVICE_ID_INTEL_BSW_UART1:
	case PCI_DEVICE_ID_INTEL_BDW_UART1:
		param->src_id = 3;
		param->dst_id = 2;
		break;
	case PCI_DEVICE_ID_INTEL_BYT_UART2:
	case PCI_DEVICE_ID_INTEL_BSW_UART2:
	case PCI_DEVICE_ID_INTEL_BDW_UART2:
		param->src_id = 5;
		param->dst_id = 4;
		break;
	default:
		return -EINVAL;
	}

	param->dma_dev = &dma_dev->dev;
	param->m_master = 0;
	param->p_master = 1;

	lpss->dma_maxburst = 16;

	port->set_termios = byt_set_termios;
	port->get_mctrl = byt_get_mctrl;

	/* Disable TX counter interrupts */
	writel(BYT_TX_OVF_INT_MASK, port->membase + BYT_TX_OVF_INT);

	return 0;
}