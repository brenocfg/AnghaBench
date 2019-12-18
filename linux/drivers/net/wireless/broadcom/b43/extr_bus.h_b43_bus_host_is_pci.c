#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct b43_bus_dev {scalar_t__ bus_type; TYPE_4__* sdev; TYPE_2__* bdev; } ;
struct TYPE_8__ {TYPE_3__* bus; } ;
struct TYPE_7__ {scalar_t__ bustype; } ;
struct TYPE_6__ {TYPE_1__* bus; } ;
struct TYPE_5__ {scalar_t__ hosttype; } ;

/* Variables and functions */
 scalar_t__ B43_BUS_BCMA ; 
 scalar_t__ B43_BUS_SSB ; 
 scalar_t__ BCMA_HOSTTYPE_PCI ; 
 scalar_t__ SSB_BUSTYPE_PCI ; 

__attribute__((used)) static inline bool b43_bus_host_is_pci(struct b43_bus_dev *dev)
{
#ifdef CONFIG_B43_BCMA
	if (dev->bus_type == B43_BUS_BCMA)
		return (dev->bdev->bus->hosttype == BCMA_HOSTTYPE_PCI);
#endif
#ifdef CONFIG_B43_SSB
	if (dev->bus_type == B43_BUS_SSB)
		return (dev->sdev->bus->bustype == SSB_BUSTYPE_PCI);
#endif
	return false;
}