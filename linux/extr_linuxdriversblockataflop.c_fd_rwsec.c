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
struct TYPE_4__ {int stretch; int spt; } ;
struct TYPE_3__ {unsigned char dma_lo; unsigned char dma_md; unsigned char dma_hi; int dma_mode_status; int fdc_acces_seccount; } ;

/* Variables and functions */
 scalar_t__ ATARIHW_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMABuffer ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  EXTD_DMA ; 
 int FDCCMDADD_M ; 
 int FDCCMD_RDSEC ; 
 int FDCCMD_WRSEC ; 
 int /*<<< orphan*/  FDCREG_SECTOR ; 
 int /*<<< orphan*/  FDCREG_TRACK ; 
 unsigned int FDCSELREG_STP ; 
 unsigned int FDC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FDC_WRITE (int /*<<< orphan*/ ,unsigned int) ; 
 int HZ ; 
 int /*<<< orphan*/  MFPDELAY () ; 
 unsigned int MotorOn ; 
 int MultReadInProgress ; 
 int NeedSeek ; 
 unsigned long PhysDMABuffer ; 
 unsigned long PhysTrackBuffer ; 
 scalar_t__ ReqCmd ; 
 int /*<<< orphan*/  ReqData ; 
 int ReqSector ; 
 int /*<<< orphan*/  ReqSide ; 
 int /*<<< orphan*/  SET_IRQ_HANDLER (int /*<<< orphan*/ ) ; 
 TYPE_2__* SUDT ; 
 scalar_t__ WRITE ; 
 int /*<<< orphan*/  copy_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cache_maintenance (unsigned long,int,int) ; 
 TYPE_1__ dma_wd ; 
 int /*<<< orphan*/  fd_rwsec_done ; 
 int /*<<< orphan*/  fd_select_side (int /*<<< orphan*/ ) ; 
 int get_head_settle_flag () ; 
 int jiffies ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int) ; 
 scalar_t__ read_track ; 
 int /*<<< orphan*/  readtrack_timer ; 
 unsigned short st_dma_ext_dmahi ; 
 int /*<<< orphan*/  start_timeout () ; 
 int /*<<< orphan*/  udelay (int) ; 
 unsigned long virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fd_rwsec( void )
{
	unsigned long paddr, flags;
	unsigned int  rwflag, old_motoron;
	unsigned int track;
	
	DPRINT(("fd_rwsec(), Sec=%d, Access=%c\n",ReqSector, ReqCmd == WRITE ? 'w' : 'r' ));
	if (ReqCmd == WRITE) {
		if (ATARIHW_PRESENT(EXTD_DMA)) {
			paddr = virt_to_phys(ReqData);
		}
		else {
			copy_buffer( ReqData, DMABuffer );
			paddr = PhysDMABuffer;
		}
		dma_cache_maintenance( paddr, 512, 1 );
		rwflag = 0x100;
	}
	else {
		if (read_track)
			paddr = PhysTrackBuffer;
		else
			paddr = ATARIHW_PRESENT(EXTD_DMA) ? 
				virt_to_phys(ReqData) : PhysDMABuffer;
		rwflag = 0;
	}

	fd_select_side( ReqSide );
  
	/* Start sector of this operation */
	FDC_WRITE( FDCREG_SECTOR, read_track ? 1 : ReqSector );
	MFPDELAY();
	/* Cheat for track if stretch != 0 */
	if (SUDT->stretch) {
		track = FDC_READ( FDCREG_TRACK);
		MFPDELAY();
		FDC_WRITE( FDCREG_TRACK, track >> SUDT->stretch);
	}
	udelay(25);
  
	/* Setup DMA */
	local_irq_save(flags);
	dma_wd.dma_lo = (unsigned char)paddr;
	MFPDELAY();
	paddr >>= 8;
	dma_wd.dma_md = (unsigned char)paddr;
	MFPDELAY();
	paddr >>= 8;
	if (ATARIHW_PRESENT(EXTD_DMA))
		st_dma_ext_dmahi = (unsigned short)paddr;
	else
		dma_wd.dma_hi = (unsigned char)paddr;
	MFPDELAY();
	local_irq_restore(flags);
  
	/* Clear FIFO and switch DMA to correct mode */  
	dma_wd.dma_mode_status = 0x90 | rwflag;  
	MFPDELAY();
	dma_wd.dma_mode_status = 0x90 | (rwflag ^ 0x100);  
	MFPDELAY();
	dma_wd.dma_mode_status = 0x90 | rwflag;
	MFPDELAY();
  
	/* How many sectors for DMA */
	dma_wd.fdc_acces_seccount = read_track ? SUDT->spt : 1;
  
	udelay(25);  
  
	/* Start operation */
	dma_wd.dma_mode_status = FDCSELREG_STP | rwflag;
	udelay(25);
	SET_IRQ_HANDLER( fd_rwsec_done );
	dma_wd.fdc_acces_seccount =
	  (get_head_settle_flag() |
	   (rwflag ? FDCCMD_WRSEC : (FDCCMD_RDSEC | (read_track ? FDCCMDADD_M : 0))));

	old_motoron = MotorOn;
	MotorOn = 1;
	NeedSeek = 1;
	/* wait for interrupt */

	if (read_track) {
		/* If reading a whole track, wait about one disk rotation and
		 * then check if all sectors are read. The FDC will even
		 * search for the first non-existent sector and need 1 sec to
		 * recognise that it isn't present :-(
		 */
		MultReadInProgress = 1;
		mod_timer(&readtrack_timer,
			  /* 1 rot. + 5 rot.s if motor was off  */
			  jiffies + HZ/5 + (old_motoron ? 0 : HZ));
	}
	start_timeout();
}