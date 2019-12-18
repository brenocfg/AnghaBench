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
struct pci_dev {int dummy; } ;
struct msi_desc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

struct pci_dev *msi_desc_to_pci_dev(struct msi_desc *desc)
{
	return to_pci_dev(desc->dev);
}