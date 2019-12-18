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
struct socket_data {int /*<<< orphan*/  io_db; } ;
struct resource {int dummy; } ;
struct pcmcia_socket {TYPE_1__* cb_dev; struct socket_data* resource_data; int /*<<< orphan*/  dev; } ;
struct pcmcia_align_data {unsigned long mask; unsigned long offset; int /*<<< orphan*/ * map; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int allocate_resource (int /*<<< orphan*/ *,struct resource*,int,unsigned long,unsigned long,int,int /*<<< orphan*/ ,struct pcmcia_align_data*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioport_resource ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 int pci_bus_alloc_resource (int /*<<< orphan*/ ,struct resource*,int,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pcmcia_align_data*) ; 
 int /*<<< orphan*/  pcmcia_align ; 
 struct resource* pcmcia_make_resource (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource *__nonstatic_find_io_region(struct pcmcia_socket *s,
						unsigned long base, int num,
						unsigned long align)
{
	struct resource *res = pcmcia_make_resource(0, num, IORESOURCE_IO,
						dev_name(&s->dev));
	struct socket_data *s_data = s->resource_data;
	struct pcmcia_align_data data;
	unsigned long min = base;
	int ret;

	data.mask = align - 1;
	data.offset = base & data.mask;
	data.map = &s_data->io_db;

#ifdef CONFIG_PCI
	if (s->cb_dev) {
		ret = pci_bus_alloc_resource(s->cb_dev->bus, res, num, 1,
					     min, 0, pcmcia_align, &data);
	} else
#endif
		ret = allocate_resource(&ioport_resource, res, num, min, ~0UL,
					1, pcmcia_align, &data);

	if (ret != 0) {
		kfree(res);
		res = NULL;
	}
	return res;
}