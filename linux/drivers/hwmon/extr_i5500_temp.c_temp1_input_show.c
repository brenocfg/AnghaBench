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
typedef  scalar_t__ u16 ;
struct pci_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  long s8 ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TSFSC ; 
 int /*<<< orphan*/  REG_TSTHRHI ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t temp1_input_show(struct device *dev,
				struct device_attribute *devattr, char *buf)
{
	struct pci_dev *pdev = to_pci_dev(dev->parent);
	long temp;
	u16 tsthrhi;
	s8 tsfsc;

	pci_read_config_word(pdev, REG_TSTHRHI, &tsthrhi);
	pci_read_config_byte(pdev, REG_TSFSC, &tsfsc);
	temp = ((long)tsthrhi - tsfsc) * 500;

	return sprintf(buf, "%ld\n", temp);
}