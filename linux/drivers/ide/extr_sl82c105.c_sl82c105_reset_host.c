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
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int,int) ; 

__attribute__((used)) static inline void sl82c105_reset_host(struct pci_dev *dev)
{
	u16 val;

	pci_read_config_word(dev, 0x7e, &val);
	pci_write_config_word(dev, 0x7e, val | (1 << 2));
	pci_write_config_word(dev, 0x7e, val & ~(1 << 2));
}