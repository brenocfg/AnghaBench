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
typedef  int /*<<< orphan*/  u16 ;
struct set_msi_sid_data {scalar_t__ count; int /*<<< orphan*/  alias; struct pci_dev* pdev; int /*<<< orphan*/  busmatch_count; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ PCI_BUS_NUM (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_msi_sid_cb(struct pci_dev *pdev, u16 alias, void *opaque)
{
	struct set_msi_sid_data *data = opaque;

	if (data->count == 0 || PCI_BUS_NUM(alias) == PCI_BUS_NUM(data->alias))
		data->busmatch_count++;

	data->pdev = pdev;
	data->alias = alias;
	data->count++;

	return 0;
}