#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sta2x11_mfd_setup_data {TYPE_2__* bars; } ;
struct pci_dev {int dummy; } ;
typedef  int /*<<< orphan*/  pdev ;
struct TYPE_4__ {int ncells; TYPE_1__* cells; } ;
struct TYPE_3__ {int pdata_size; struct pci_dev** platform_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 

__attribute__((used)) static void sta2x11_mfd_setup(struct pci_dev *pdev,
			      struct sta2x11_mfd_setup_data *sd)
{
	int i, j;
	for (i = 0; i < ARRAY_SIZE(sd->bars); i++)
		for (j = 0; j < sd->bars[i].ncells; j++) {
			sd->bars[i].cells[j].pdata_size = sizeof(pdev);
			sd->bars[i].cells[j].platform_data = &pdev;
		}
}