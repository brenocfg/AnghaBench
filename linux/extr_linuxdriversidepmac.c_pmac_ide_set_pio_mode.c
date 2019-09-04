#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  unsigned int u32 ;
struct ide_timing {unsigned int active; unsigned int setup; } ;
struct TYPE_11__ {unsigned int* timings; int kind; } ;
typedef  TYPE_2__ pmac_ide_hwif_t ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct TYPE_12__ {TYPE_1__ gendev; } ;
typedef  TYPE_3__ ide_hwif_t ;
struct TYPE_13__ {int dn; scalar_t__ const pio_mode; } ;
typedef  TYPE_4__ ide_drive_t ;

/* Variables and functions */
 unsigned int SYSCLK_TICKS (unsigned int) ; 
 unsigned int SYSCLK_TICKS_66 (unsigned int) ; 
 unsigned int TR_100_PIOREG_PIO_MASK ; 
 unsigned int TR_133_PIOREG_PIO_MASK ; 
 unsigned int TR_33_PIO_ACCESS_SHIFT ; 
 unsigned int TR_33_PIO_E ; 
 unsigned int TR_33_PIO_MASK ; 
 unsigned int TR_33_PIO_RECOVERY_SHIFT ; 
 unsigned int TR_66_PIO_ACCESS_SHIFT ; 
 unsigned int TR_66_PIO_MASK ; 
 unsigned int TR_66_PIO_RECOVERY_SHIFT ; 
 scalar_t__ const XFER_PIO_0 ; 
#define  controller_k2_ata6 131 
#define  controller_kl_ata4 130 
#define  controller_sh_ata6 129 
#define  controller_un_ata6 128 
 TYPE_2__* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 unsigned int ide_pio_cycle_time (TYPE_4__*,scalar_t__ const) ; 
 struct ide_timing* ide_timing_find_mode (scalar_t__ const) ; 
 unsigned int kauai_lookup_timing (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kauai_pio_timings ; 
 unsigned int max (unsigned int,unsigned int) ; 
 unsigned int min (unsigned int,int) ; 
 int /*<<< orphan*/  pmac_ide_do_update_timings (TYPE_4__*) ; 
 int /*<<< orphan*/  shasta_pio_timings ; 

__attribute__((used)) static void pmac_ide_set_pio_mode(ide_hwif_t *hwif, ide_drive_t *drive)
{
	pmac_ide_hwif_t *pmif = dev_get_drvdata(hwif->gendev.parent);
	const u8 pio = drive->pio_mode - XFER_PIO_0;
	struct ide_timing *tim = ide_timing_find_mode(XFER_PIO_0 + pio);
	u32 *timings, t;
	unsigned accessTicks, recTicks;
	unsigned accessTime, recTime;
	unsigned int cycle_time;

	/* which drive is it ? */
	timings = &pmif->timings[drive->dn & 1];
	t = *timings;

	cycle_time = ide_pio_cycle_time(drive, pio);

	switch (pmif->kind) {
	case controller_sh_ata6: {
		/* 133Mhz cell */
		u32 tr = kauai_lookup_timing(shasta_pio_timings, cycle_time);
		t = (t & ~TR_133_PIOREG_PIO_MASK) | tr;
		break;
		}
	case controller_un_ata6:
	case controller_k2_ata6: {
		/* 100Mhz cell */
		u32 tr = kauai_lookup_timing(kauai_pio_timings, cycle_time);
		t = (t & ~TR_100_PIOREG_PIO_MASK) | tr;
		break;
		}
	case controller_kl_ata4:
		/* 66Mhz cell */
		recTime = cycle_time - tim->active - tim->setup;
		recTime = max(recTime, 150U);
		accessTime = tim->active;
		accessTime = max(accessTime, 150U);
		accessTicks = SYSCLK_TICKS_66(accessTime);
		accessTicks = min(accessTicks, 0x1fU);
		recTicks = SYSCLK_TICKS_66(recTime);
		recTicks = min(recTicks, 0x1fU);
		t = (t & ~TR_66_PIO_MASK) |
			(accessTicks << TR_66_PIO_ACCESS_SHIFT) |
			(recTicks << TR_66_PIO_RECOVERY_SHIFT);
		break;
	default: {
		/* 33Mhz cell */
		int ebit = 0;
		recTime = cycle_time - tim->active - tim->setup;
		recTime = max(recTime, 150U);
		accessTime = tim->active;
		accessTime = max(accessTime, 150U);
		accessTicks = SYSCLK_TICKS(accessTime);
		accessTicks = min(accessTicks, 0x1fU);
		accessTicks = max(accessTicks, 4U);
		recTicks = SYSCLK_TICKS(recTime);
		recTicks = min(recTicks, 0x1fU);
		recTicks = max(recTicks, 5U) - 4;
		if (recTicks > 9) {
			recTicks--; /* guess, but it's only for PIO0, so... */
			ebit = 1;
		}
		t = (t & ~TR_33_PIO_MASK) |
				(accessTicks << TR_33_PIO_ACCESS_SHIFT) |
				(recTicks << TR_33_PIO_RECOVERY_SHIFT);
		if (ebit)
			t |= TR_33_PIO_E;
		break;
		}
	}

#ifdef IDE_PMAC_DEBUG
	printk(KERN_ERR "%s: Set PIO timing for mode %d, reg: 0x%08x\n",
		drive->name, pio,  *timings);
#endif	

	*timings = t;
	pmac_ide_do_update_timings(drive);
}