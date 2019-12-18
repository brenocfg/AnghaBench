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
struct resource {scalar_t__ end; scalar_t__ start; TYPE_1__* parent; void* flags; } ;
struct pci_dev {TYPE_1__* resource; } ;
struct mfd_cell {char* name; int num_resources; int pdata_size; struct janz_platform_data* platform_data; scalar_t__ id; struct resource* resources; } ;
struct janz_platform_data {unsigned int modno; } ;
struct cmodio_device {struct janz_platform_data* pdata; struct resource* resources; struct mfd_cell* cells; struct pci_dev* pdev; } ;
struct TYPE_2__ {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 unsigned int CMODIO_MODULBUS_SIZE ; 
 void* IORESOURCE_IRQ ; 
 void* IORESOURCE_MEM ; 
 int /*<<< orphan*/  cmodio_id ; 

__attribute__((used)) static int cmodio_setup_subdevice(struct cmodio_device *priv,
					    char *name, unsigned int devno,
					    unsigned int modno)
{
	struct janz_platform_data *pdata;
	struct mfd_cell *cell;
	struct resource *res;
	struct pci_dev *pci;

	pci = priv->pdev;
	cell = &priv->cells[devno];
	res = &priv->resources[devno * 3];
	pdata = &priv->pdata[devno];

	cell->name = name;
	cell->resources = res;
	cell->num_resources = 3;

	/* Setup the subdevice ID -- must be unique */
	cell->id = cmodio_id++;

	/* Add platform data */
	pdata->modno = modno;
	cell->platform_data = pdata;
	cell->pdata_size = sizeof(*pdata);

	/* MODULbus registers -- PCI BAR3 is big-endian MODULbus access */
	res->flags = IORESOURCE_MEM;
	res->parent = &pci->resource[3];
	res->start = pci->resource[3].start + (CMODIO_MODULBUS_SIZE * modno);
	res->end = res->start + CMODIO_MODULBUS_SIZE - 1;
	res++;

	/* PLX Control Registers -- PCI BAR4 is interrupt and other registers */
	res->flags = IORESOURCE_MEM;
	res->parent = &pci->resource[4];
	res->start = pci->resource[4].start;
	res->end = pci->resource[4].end;
	res++;

	/*
	 * IRQ
	 *
	 * The start and end fields are used as an offset to the irq_base
	 * parameter passed into the mfd_add_devices() function call. All
	 * devices share the same IRQ.
	 */
	res->flags = IORESOURCE_IRQ;
	res->parent = NULL;
	res->start = 0;
	res->end = 0;
	res++;

	return 0;
}