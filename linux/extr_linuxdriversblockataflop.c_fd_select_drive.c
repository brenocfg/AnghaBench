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
struct TYPE_8__ {int /*<<< orphan*/  track; } ;
struct TYPE_7__ {int /*<<< orphan*/  fdc_speed; } ;
struct TYPE_6__ {int /*<<< orphan*/  fdc_speed; } ;
struct TYPE_5__ {int rd_data_reg_sel; unsigned char wd_data; } ;

/* Variables and functions */
 scalar_t__ ATARIHW_PRESENT (int /*<<< orphan*/ ) ; 
 unsigned char DSKDRV0 ; 
 unsigned char DSKDRV1 ; 
 unsigned char DSKDRVNONE ; 
 int /*<<< orphan*/  FDCREG_TRACK ; 
 int /*<<< orphan*/  FDCSPEED ; 
 int /*<<< orphan*/  FDC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SelectedDrive ; 
 TYPE_4__ UD ; 
 TYPE_3__* UDT ; 
 int atari_dont_touch_floppy_select ; 
 TYPE_2__ dma_wd ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_1__ sound_ym ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void fd_select_drive( int drive )
{
	unsigned long flags;
	unsigned char tmp;
  
	if (drive == SelectedDrive)
	  return;

	/* protect against various other ints mucking around with the PSG */
	local_irq_save(flags);
	sound_ym.rd_data_reg_sel = 14; /* Select PSG Port A */
	tmp = sound_ym.rd_data_reg_sel;
	sound_ym.wd_data = (tmp | DSKDRVNONE) & ~(drive == 0 ? DSKDRV0 : DSKDRV1);
	atari_dont_touch_floppy_select = 1;
	local_irq_restore(flags);

	/* restore track register to saved value */
	FDC_WRITE( FDCREG_TRACK, UD.track );
	udelay(25);

	/* select 8/16 MHz */
	if (UDT)
		if (ATARIHW_PRESENT(FDCSPEED))
			dma_wd.fdc_speed = UDT->fdc_speed;
	
	SelectedDrive = drive;
}