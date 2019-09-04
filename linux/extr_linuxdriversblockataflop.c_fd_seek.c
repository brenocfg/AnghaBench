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
struct TYPE_6__ {int track; int steprate; } ;
struct TYPE_5__ {int stretch; } ;
struct TYPE_4__ {scalar_t__ fdc_speed; } ;

/* Variables and functions */
 scalar_t__ ATARIHW_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int FDCCMD_SEEK ; 
 int /*<<< orphan*/  FDCREG_CMD ; 
 int /*<<< orphan*/  FDCREG_DATA ; 
 int /*<<< orphan*/  FDCSPEED ; 
 int /*<<< orphan*/  FDC_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MFPDELAY () ; 
 int MotorOn ; 
 int ReqTrack ; 
 int /*<<< orphan*/  SET_IRQ_HANDLER (int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 TYPE_3__ SUD ; 
 TYPE_2__* SUDT ; 
 TYPE_1__ dma_wd ; 
 int /*<<< orphan*/  fd_seek_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_head_settle_flag () ; 
 int /*<<< orphan*/  start_timeout () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void fd_seek( void )
{
	if (SUD.track == ReqTrack << SUDT->stretch) {
		fd_seek_done( 0 );
		return;
	}

	if (ATARIHW_PRESENT(FDCSPEED)) {
		dma_wd.fdc_speed = 0;	/* always seek witch 8 Mhz */
		MFPDELAY();
	}

	DPRINT(("fd_seek() to track %d\n",ReqTrack));
	FDC_WRITE( FDCREG_DATA, ReqTrack << SUDT->stretch);
	udelay(25);
	SET_IRQ_HANDLER( fd_seek_done );
	FDC_WRITE( FDCREG_CMD, FDCCMD_SEEK | SUD.steprate );

	MotorOn = 1;
	set_head_settle_flag();
	start_timeout();
	/* wait for IRQ */
}