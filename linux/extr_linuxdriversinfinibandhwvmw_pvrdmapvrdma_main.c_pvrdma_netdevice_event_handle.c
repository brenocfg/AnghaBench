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
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct pvrdma_dev {TYPE_2__ ib_dev; TYPE_1__* pdev; struct net_device* netdev; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_PORT_ACTIVE ; 
 int /*<<< orphan*/  IB_EVENT_PORT_ERR ; 
#define  NETDEV_DOWN 132 
#define  NETDEV_REBOOT 131 
#define  NETDEV_REGISTER 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int /*<<< orphan*/  PCI_DEVFN (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PVRDMA_DEVICE_CTL_UNQUIESCE ; 
 int /*<<< orphan*/  PVRDMA_REG_CTL ; 
 int /*<<< orphan*/  PVRDMA_REG_ERR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvrdma_dispatch_event (struct pvrdma_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvrdma_read_reg (struct pvrdma_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvrdma_write_reg (struct pvrdma_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvrdma_netdevice_event_handle(struct pvrdma_dev *dev,
					  struct net_device *ndev,
					  unsigned long event)
{
	struct pci_dev *pdev_net;
	unsigned int slot;

	switch (event) {
	case NETDEV_REBOOT:
	case NETDEV_DOWN:
		pvrdma_dispatch_event(dev, 1, IB_EVENT_PORT_ERR);
		break;
	case NETDEV_UP:
		pvrdma_write_reg(dev, PVRDMA_REG_CTL,
				 PVRDMA_DEVICE_CTL_UNQUIESCE);

		mb();

		if (pvrdma_read_reg(dev, PVRDMA_REG_ERR))
			dev_err(&dev->pdev->dev,
				"failed to activate device during link up\n");
		else
			pvrdma_dispatch_event(dev, 1, IB_EVENT_PORT_ACTIVE);
		break;
	case NETDEV_UNREGISTER:
		dev_put(dev->netdev);
		dev->netdev = NULL;
		break;
	case NETDEV_REGISTER:
		/* vmxnet3 will have same bus, slot. But func will be 0 */
		slot = PCI_SLOT(dev->pdev->devfn);
		pdev_net = pci_get_slot(dev->pdev->bus,
					PCI_DEVFN(slot, 0));
		if ((dev->netdev == NULL) &&
		    (pci_get_drvdata(pdev_net) == ndev)) {
			/* this is our netdev */
			dev->netdev = ndev;
			dev_hold(ndev);
		}
		pci_dev_put(pdev_net);
		break;

	default:
		dev_dbg(&dev->pdev->dev, "ignore netdevice event %ld on %s\n",
			event, dev->ib_dev.name);
		break;
	}
}