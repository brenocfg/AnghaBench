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
typedef  int u32 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int EIO ; 
 int /*<<< orphan*/  GPIO_BASE ; 
 int /*<<< orphan*/  GPIO_CTRL ; 
 int GPIO_EN ; 
 int /*<<< orphan*/  ICH7_GPIO_SIZE ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  PMBASE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int g_pm_io_base ; 
 int /*<<< orphan*/ * gp_gpio_resource ; 
 int /*<<< orphan*/  ich7_gpio_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ich7_lpc_cleanup (int /*<<< orphan*/ *) ; 
 int nas_gpio_io_base ; 
 struct pci_dev* nas_gpio_pci_dev ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * request_region (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ich7_lpc_probe(struct pci_dev *dev,
				    const struct pci_device_id *id)
{
	int status;
	u32 gc = 0;

	status = pci_enable_device(dev);
	if (status) {
		dev_err(&dev->dev, "pci_enable_device failed\n");
		return -EIO;
	}

	nas_gpio_pci_dev = dev;
	status = pci_read_config_dword(dev, PMBASE, &g_pm_io_base);
	if (status)
		goto out;
	g_pm_io_base &= 0x00000ff80;

	status = pci_read_config_dword(dev, GPIO_CTRL, &gc);
	if (!(GPIO_EN & gc)) {
		status = -EEXIST;
		dev_info(&dev->dev,
			   "ERROR: The LPC GPIO Block has not been enabled.\n");
		goto out;
	}

	status = pci_read_config_dword(dev, GPIO_BASE, &nas_gpio_io_base);
	if (0 > status) {
		dev_info(&dev->dev, "Unable to read GPIOBASE.\n");
		goto out;
	}
	dev_dbg(&dev->dev, ": GPIOBASE = 0x%08x\n", nas_gpio_io_base);
	nas_gpio_io_base &= 0x00000ffc0;

	/*
	 * Insure that we have exclusive access to the GPIO I/O address range.
	 */
	gp_gpio_resource = request_region(nas_gpio_io_base, ICH7_GPIO_SIZE,
					  KBUILD_MODNAME);
	if (NULL == gp_gpio_resource) {
		dev_info(&dev->dev,
			 "ERROR Unable to register GPIO I/O addresses.\n");
		status = -1;
		goto out;
	}

	/*
	 * Initialize the GPIO for NAS/Home Server Use
	 */
	ich7_gpio_init(&dev->dev);

out:
	if (status) {
		ich7_lpc_cleanup(&dev->dev);
		pci_disable_device(dev);
	}
	return status;
}