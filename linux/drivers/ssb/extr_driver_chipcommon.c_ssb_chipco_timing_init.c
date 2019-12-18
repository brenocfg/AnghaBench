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
typedef  int u32 ;
struct TYPE_2__ {int revision; } ;
struct ssb_device {TYPE_1__ id; struct ssb_bus* bus; } ;
struct ssb_chipcommon {struct ssb_device* dev; } ;
struct ssb_bus {int chip_id; scalar_t__ chip_rev; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,unsigned long) ; 
 int /*<<< orphan*/  SSB_CHIPCO_FLASH_WAITCNT ; 
 int /*<<< orphan*/  SSB_CHIPCO_PCMCIA_MEMWAIT ; 
 int /*<<< orphan*/  SSB_CHIPCO_PROG_CFG ; 
 int /*<<< orphan*/  SSB_CHIPCO_PROG_WAITCNT ; 
 int SSB_FLASH_WCNT_1_SHIFT ; 
 int SSB_FLASH_WCNT_3_SHIFT ; 
 int SSB_PROG_WCNT_1_SHIFT ; 
 int SSB_PROG_WCNT_2_SHIFT ; 
 int SSB_PROG_WCNT_3_SHIFT ; 
 int /*<<< orphan*/  chipco_write32 (struct ssb_chipcommon*,int /*<<< orphan*/ ,int) ; 

void ssb_chipco_timing_init(struct ssb_chipcommon *cc,
			    unsigned long ns)
{
	struct ssb_device *dev = cc->dev;
	struct ssb_bus *bus = dev->bus;
	u32 tmp;

	/* set register for external IO to control LED. */
	chipco_write32(cc, SSB_CHIPCO_PROG_CFG, 0x11);
	tmp = DIV_ROUND_UP(10, ns) << SSB_PROG_WCNT_3_SHIFT;		/* Waitcount-3 = 10ns */
	tmp |= DIV_ROUND_UP(40, ns) << SSB_PROG_WCNT_1_SHIFT;	/* Waitcount-1 = 40ns */
	tmp |= DIV_ROUND_UP(240, ns);				/* Waitcount-0 = 240ns */
	chipco_write32(cc, SSB_CHIPCO_PROG_WAITCNT, tmp);	/* 0x01020a0c for a 100Mhz clock */

	/* Set timing for the flash */
	tmp = DIV_ROUND_UP(10, ns) << SSB_FLASH_WCNT_3_SHIFT;	/* Waitcount-3 = 10nS */
	tmp |= DIV_ROUND_UP(10, ns) << SSB_FLASH_WCNT_1_SHIFT;	/* Waitcount-1 = 10nS */
	tmp |= DIV_ROUND_UP(120, ns);				/* Waitcount-0 = 120nS */
	if ((bus->chip_id == 0x5365) ||
	    (dev->id.revision < 9))
		chipco_write32(cc, SSB_CHIPCO_FLASH_WAITCNT, tmp);
	if ((bus->chip_id == 0x5365) ||
	    (dev->id.revision < 9) ||
	    ((bus->chip_id == 0x5350) && (bus->chip_rev == 0)))
		chipco_write32(cc, SSB_CHIPCO_PCMCIA_MEMWAIT, tmp);

	if (bus->chip_id == 0x5350) {
		/* Enable EXTIF */
		tmp = DIV_ROUND_UP(10, ns) << SSB_PROG_WCNT_3_SHIFT;	  /* Waitcount-3 = 10ns */
		tmp |= DIV_ROUND_UP(20, ns) << SSB_PROG_WCNT_2_SHIFT;  /* Waitcount-2 = 20ns */
		tmp |= DIV_ROUND_UP(100, ns) << SSB_PROG_WCNT_1_SHIFT; /* Waitcount-1 = 100ns */
		tmp |= DIV_ROUND_UP(120, ns);			  /* Waitcount-0 = 120ns */
		chipco_write32(cc, SSB_CHIPCO_PROG_WAITCNT, tmp); /* 0x01020a0c for a 100Mhz clock */
	}
}