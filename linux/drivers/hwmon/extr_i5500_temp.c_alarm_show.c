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
typedef  scalar_t__ u8 ;
struct pci_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CTSTS ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t alarm_show(struct device *dev,
			  struct device_attribute *devattr, char *buf)
{
	struct pci_dev *pdev = to_pci_dev(dev->parent);
	int nr = to_sensor_dev_attr(devattr)->index;
	u8 ctsts;

	pci_read_config_byte(pdev, REG_CTSTS, &ctsts);
	return sprintf(buf, "%u\n", (unsigned int)ctsts & (1 << nr));
}