#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int capabilities; TYPE_2__* dev; } ;
struct ssb_bus {scalar_t__ bustype; TYPE_3__ chipco; } ;
struct TYPE_4__ {int revision; } ;
struct TYPE_5__ {TYPE_1__ id; } ;

/* Variables and functions */
 scalar_t__ SSB_BUSTYPE_PCI ; 
 int SSB_CHIPCO_CAP_SPROM ; 

bool ssb_is_sprom_available(struct ssb_bus *bus)
{
	/* status register only exists on chipcomon rev >= 11 and we need check
	   for >= 31 only */
	/* this routine differs from specs as we do not access SPROM directly
	   on PCMCIA */
	if (bus->bustype == SSB_BUSTYPE_PCI &&
	    bus->chipco.dev &&	/* can be unavailable! */
	    bus->chipco.dev->id.revision >= 31)
		return bus->chipco.capabilities & SSB_CHIPCO_CAP_SPROM;

	return true;
}