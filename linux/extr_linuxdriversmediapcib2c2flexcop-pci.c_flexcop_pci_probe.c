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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct flexcop_pci {int /*<<< orphan*/  irq_check_work; struct pci_dev* pdev; struct flexcop_device* fc_dev; } ;
struct flexcop_device {int /*<<< orphan*/  owner; int /*<<< orphan*/ * dev; int /*<<< orphan*/  bus_type; scalar_t__ pid_filtering; int /*<<< orphan*/  stream_control; int /*<<< orphan*/  get_mac_addr; int /*<<< orphan*/  i2c_request; int /*<<< orphan*/  write_ibi_reg; int /*<<< orphan*/  read_ibi_reg; struct flexcop_pci* bus_specific; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FC_PCI ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ enable_pid_filtering ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  flexcop_device_exit (struct flexcop_device*) ; 
 int flexcop_device_initialize (struct flexcop_device*) ; 
 int /*<<< orphan*/  flexcop_device_kfree (struct flexcop_device*) ; 
 struct flexcop_device* flexcop_device_kmalloc (int) ; 
 int /*<<< orphan*/  flexcop_eeprom_check_mac_addr ; 
 int /*<<< orphan*/  flexcop_i2c_request ; 
 int flexcop_pci_dma_init (struct flexcop_pci*) ; 
 int /*<<< orphan*/  flexcop_pci_exit (struct flexcop_pci*) ; 
 int flexcop_pci_init (struct flexcop_pci*) ; 
 int /*<<< orphan*/  flexcop_pci_irq_check_work ; 
 int /*<<< orphan*/  flexcop_pci_read_ibi_reg ; 
 int /*<<< orphan*/  flexcop_pci_stream_control ; 
 int /*<<< orphan*/  flexcop_pci_write_ibi_reg ; 
 int /*<<< orphan*/  info (char*) ; 
 int irq_chk_intv ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flexcop_pci_probe(struct pci_dev *pdev,
		const struct pci_device_id *ent)
{
	struct flexcop_device *fc;
	struct flexcop_pci *fc_pci;
	int ret = -ENOMEM;

	if ((fc = flexcop_device_kmalloc(sizeof(struct flexcop_pci))) == NULL) {
		err("out of memory\n");
		return -ENOMEM;
	}

	/* general flexcop init */
	fc_pci = fc->bus_specific;
	fc_pci->fc_dev = fc;

	fc->read_ibi_reg = flexcop_pci_read_ibi_reg;
	fc->write_ibi_reg = flexcop_pci_write_ibi_reg;
	fc->i2c_request = flexcop_i2c_request;
	fc->get_mac_addr = flexcop_eeprom_check_mac_addr;
	fc->stream_control = flexcop_pci_stream_control;

	if (enable_pid_filtering)
		info("will use the HW PID filter.");
	else
		info("will pass the complete TS to the demuxer.");

	fc->pid_filtering = enable_pid_filtering;
	fc->bus_type = FC_PCI;
	fc->dev = &pdev->dev;
	fc->owner = THIS_MODULE;

	/* bus specific part */
	fc_pci->pdev = pdev;
	if ((ret = flexcop_pci_init(fc_pci)) != 0)
		goto err_kfree;

	/* init flexcop */
	if ((ret = flexcop_device_initialize(fc)) != 0)
		goto err_pci_exit;

	/* init dma */
	if ((ret = flexcop_pci_dma_init(fc_pci)) != 0)
		goto err_fc_exit;

	INIT_DELAYED_WORK(&fc_pci->irq_check_work, flexcop_pci_irq_check_work);

	if (irq_chk_intv > 0)
		schedule_delayed_work(&fc_pci->irq_check_work,
				msecs_to_jiffies(irq_chk_intv < 100 ?
					100 :
					irq_chk_intv));
	return ret;

err_fc_exit:
	flexcop_device_exit(fc);
err_pci_exit:
	flexcop_pci_exit(fc_pci);
err_kfree:
	flexcop_device_kfree(fc);
	return ret;
}