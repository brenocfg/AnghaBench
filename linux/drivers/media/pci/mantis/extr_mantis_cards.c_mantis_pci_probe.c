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
struct pci_device_id {scalar_t__ driver_data; } ;
struct pci_dev {int dummy; } ;
struct mantis_pci_drvdata {int /*<<< orphan*/  rc_map_name; struct mantis_hwconfig* hwconfig; } ;
struct mantis_pci {int /*<<< orphan*/  intmask_lock; int /*<<< orphan*/  rc_map_name; struct mantis_hwconfig* hwconfig; struct pci_dev* pdev; int /*<<< orphan*/  verbose; int /*<<< orphan*/  num; } ;
struct mantis_hwconfig {int /*<<< orphan*/ * irq_handler; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  STREAM_TO_HIF ; 
 int /*<<< orphan*/  devs ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  kfree (struct mantis_pci*) ; 
 struct mantis_pci* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mantis_dma_exit (struct mantis_pci*) ; 
 int mantis_dma_init (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_dvb_exit (struct mantis_pci*) ; 
 int mantis_dvb_init (struct mantis_pci*) ; 
 int mantis_get_mac (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_i2c_exit (struct mantis_pci*) ; 
 int mantis_i2c_init (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_input_exit (struct mantis_pci*) ; 
 int mantis_input_init (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_irq_handler ; 
 int /*<<< orphan*/  mantis_pci_exit (struct mantis_pci*) ; 
 int mantis_pci_init (struct mantis_pci*) ; 
 int mantis_stream_control (struct mantis_pci*,int /*<<< orphan*/ ) ; 
 int mantis_uart_init (struct mantis_pci*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int mantis_pci_probe(struct pci_dev *pdev,
			    const struct pci_device_id *pci_id)
{
	struct mantis_pci_drvdata *drvdata;
	struct mantis_pci *mantis;
	struct mantis_hwconfig *config;
	int err;

	mantis = kzalloc(sizeof(*mantis), GFP_KERNEL);
	if (!mantis)
		return -ENOMEM;

	drvdata			= (void *)pci_id->driver_data;
	mantis->num		= devs;
	mantis->verbose		= verbose;
	mantis->pdev		= pdev;
	config			= drvdata->hwconfig;
	config->irq_handler	= &mantis_irq_handler;
	mantis->hwconfig	= config;
	mantis->rc_map_name	= drvdata->rc_map_name;

	spin_lock_init(&mantis->intmask_lock);

	err = mantis_pci_init(mantis);
	if (err) {
		dprintk(MANTIS_ERROR, 1, "ERROR: Mantis PCI initialization failed <%d>", err);
		goto err_free_mantis;
	}

	err = mantis_stream_control(mantis, STREAM_TO_HIF);
	if (err < 0) {
		dprintk(MANTIS_ERROR, 1, "ERROR: Mantis stream control failed <%d>", err);
		goto err_pci_exit;
	}

	err = mantis_i2c_init(mantis);
	if (err < 0) {
		dprintk(MANTIS_ERROR, 1, "ERROR: Mantis I2C initialization failed <%d>", err);
		goto err_pci_exit;
	}

	err = mantis_get_mac(mantis);
	if (err < 0) {
		dprintk(MANTIS_ERROR, 1, "ERROR: Mantis MAC address read failed <%d>", err);
		goto err_i2c_exit;
	}

	err = mantis_dma_init(mantis);
	if (err < 0) {
		dprintk(MANTIS_ERROR, 1, "ERROR: Mantis DMA initialization failed <%d>", err);
		goto err_i2c_exit;
	}

	err = mantis_dvb_init(mantis);
	if (err < 0) {
		dprintk(MANTIS_ERROR, 1, "ERROR: Mantis DVB initialization failed <%d>", err);
		goto err_dma_exit;
	}

	err = mantis_input_init(mantis);
	if (err < 0) {
		dprintk(MANTIS_ERROR, 1,
			"ERROR: Mantis DVB initialization failed <%d>", err);
		goto err_dvb_exit;
	}

	err = mantis_uart_init(mantis);
	if (err < 0) {
		dprintk(MANTIS_ERROR, 1, "ERROR: Mantis UART initialization failed <%d>", err);
		goto err_input_exit;
	}

	devs++;

	return 0;

err_input_exit:
	mantis_input_exit(mantis);

err_dvb_exit:
	mantis_dvb_exit(mantis);

err_dma_exit:
	mantis_dma_exit(mantis);

err_i2c_exit:
	mantis_i2c_exit(mantis);

err_pci_exit:
	mantis_pci_exit(mantis);

err_free_mantis:
	kfree(mantis);

	return err;
}