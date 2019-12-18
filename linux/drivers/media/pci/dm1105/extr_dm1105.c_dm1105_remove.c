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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct dmx_demux {int /*<<< orphan*/  (* remove_frontend ) (struct dmx_demux*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* disconnect_frontend ) (struct dmx_demux*) ;int /*<<< orphan*/  (* close ) (struct dmx_demux*) ;} ;
struct dvb_demux {struct dmx_demux dmx; } ;
struct dvb_adapter {int dummy; } ;
struct dm1105_dev {int /*<<< orphan*/  io_mem; int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  hw_frontend; int /*<<< orphan*/  mem_frontend; scalar_t__ fe; int /*<<< orphan*/  dvbnet; struct dvb_demux demux; struct dvb_adapter dvb_adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm1105_devcount ; 
 int /*<<< orphan*/  dm1105_hw_exit (struct dm1105_dev*) ; 
 int /*<<< orphan*/  dm1105_ir_exit (struct dm1105_dev*) ; 
 int /*<<< orphan*/  dvb_dmx_release (struct dvb_demux*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (struct dvb_adapter*) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct dm1105_dev*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dm1105_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct dm1105_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  stub1 (struct dmx_demux*) ; 
 int /*<<< orphan*/  stub2 (struct dmx_demux*) ; 
 int /*<<< orphan*/  stub3 (struct dmx_demux*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct dmx_demux*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dm1105_remove(struct pci_dev *pdev)
{
	struct dm1105_dev *dev = pci_get_drvdata(pdev);
	struct dvb_adapter *dvb_adapter = &dev->dvb_adapter;
	struct dvb_demux *dvbdemux = &dev->demux;
	struct dmx_demux *dmx = &dvbdemux->dmx;

	dm1105_ir_exit(dev);
	dmx->close(dmx);
	dvb_net_release(&dev->dvbnet);
	if (dev->fe)
		dvb_unregister_frontend(dev->fe);

	dmx->disconnect_frontend(dmx);
	dmx->remove_frontend(dmx, &dev->mem_frontend);
	dmx->remove_frontend(dmx, &dev->hw_frontend);
	dvb_dmxdev_release(&dev->dmxdev);
	dvb_dmx_release(dvbdemux);
	dvb_unregister_adapter(dvb_adapter);
	i2c_del_adapter(&dev->i2c_adap);

	dm1105_hw_exit(dev);
	free_irq(pdev->irq, dev);
	pci_iounmap(pdev, dev->io_mem);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	dm1105_devcount--;
	kfree(dev);
}