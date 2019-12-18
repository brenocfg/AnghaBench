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
struct TYPE_2__ {int /*<<< orphan*/  shutdown; int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; } ;
struct spi_mem_driver {TYPE_1__ spidrv; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int __spi_register_driver (struct module*,TYPE_1__*) ; 
 int /*<<< orphan*/  spi_mem_probe ; 
 int /*<<< orphan*/  spi_mem_remove ; 
 int /*<<< orphan*/  spi_mem_shutdown ; 

int spi_mem_driver_register_with_owner(struct spi_mem_driver *memdrv,
				       struct module *owner)
{
	memdrv->spidrv.probe = spi_mem_probe;
	memdrv->spidrv.remove = spi_mem_remove;
	memdrv->spidrv.shutdown = spi_mem_shutdown;

	return __spi_register_driver(owner, &memdrv->spidrv);
}