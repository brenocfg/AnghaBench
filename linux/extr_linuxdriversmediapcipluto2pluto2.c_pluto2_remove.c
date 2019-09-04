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
struct dmx_demux {int /*<<< orphan*/  (* remove_frontend ) (struct dmx_demux*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* disconnect_frontend ) (struct dmx_demux*) ;int /*<<< orphan*/  (* close ) (struct dmx_demux*) ;} ;
struct dvb_demux {struct dmx_demux dmx; } ;
struct dvb_adapter {int dummy; } ;
struct pluto {int /*<<< orphan*/  io_mem; int /*<<< orphan*/  i2c_adap; int /*<<< orphan*/  dmxdev; int /*<<< orphan*/  hw_frontend; int /*<<< orphan*/  mem_frontend; scalar_t__ fe; int /*<<< orphan*/  dvbnet; struct dvb_demux demux; struct dvb_adapter dvb_adapter; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_dmx_release (struct dvb_demux*) ; 
 int /*<<< orphan*/  dvb_dmxdev_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_net_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_unregister_adapter (struct dvb_adapter*) ; 
 int /*<<< orphan*/  dvb_unregister_frontend (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pluto*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pluto*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct pluto* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pluto_hw_exit (struct pluto*) ; 
 int /*<<< orphan*/  stub1 (struct dmx_demux*) ; 
 int /*<<< orphan*/  stub2 (struct dmx_demux*) ; 
 int /*<<< orphan*/  stub3 (struct dmx_demux*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct dmx_demux*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pluto2_remove(struct pci_dev *pdev)
{
	struct pluto *pluto = pci_get_drvdata(pdev);
	struct dvb_adapter *dvb_adapter = &pluto->dvb_adapter;
	struct dvb_demux *dvbdemux = &pluto->demux;
	struct dmx_demux *dmx = &dvbdemux->dmx;

	dmx->close(dmx);
	dvb_net_release(&pluto->dvbnet);
	if (pluto->fe)
		dvb_unregister_frontend(pluto->fe);

	dmx->disconnect_frontend(dmx);
	dmx->remove_frontend(dmx, &pluto->mem_frontend);
	dmx->remove_frontend(dmx, &pluto->hw_frontend);
	dvb_dmxdev_release(&pluto->dmxdev);
	dvb_dmx_release(dvbdemux);
	dvb_unregister_adapter(dvb_adapter);
	i2c_del_adapter(&pluto->i2c_adap);
	pluto_hw_exit(pluto);
	free_irq(pdev->irq, pluto);
	pci_iounmap(pdev, pluto->io_mem);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	kfree(pluto);
}