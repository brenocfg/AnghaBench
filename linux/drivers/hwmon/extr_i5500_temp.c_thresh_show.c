#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t thresh_show(struct device *dev,
			   struct device_attribute *devattr, char *buf)
{
	struct pci_dev *pdev = to_pci_dev(dev->parent);
	int reg = to_sensor_dev_attr(devattr)->index;
	long temp;
	u16 tsthr;

	pci_read_config_word(pdev, reg, &tsthr);
	temp = tsthr * 500;

	return sprintf(buf, "%ld\n", temp);
}