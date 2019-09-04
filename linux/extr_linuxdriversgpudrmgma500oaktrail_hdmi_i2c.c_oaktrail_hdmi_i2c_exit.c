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
struct oaktrail_hdmi_dev {struct hdmi_i2c_dev* i2c_dev; } ;
struct hdmi_i2c_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct oaktrail_hdmi_dev*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hdmi_i2c_dev*) ; 
 int /*<<< orphan*/  oaktrail_hdmi_i2c_adapter ; 
 struct oaktrail_hdmi_dev* pci_get_drvdata (struct pci_dev*) ; 

void oaktrail_hdmi_i2c_exit(struct pci_dev *dev)
{
	struct oaktrail_hdmi_dev *hdmi_dev;
	struct hdmi_i2c_dev *i2c_dev;

	hdmi_dev = pci_get_drvdata(dev);
	i2c_del_adapter(&oaktrail_hdmi_i2c_adapter);

	i2c_dev = hdmi_dev->i2c_dev;
	kfree(i2c_dev);
	free_irq(dev->irq, hdmi_dev);
}