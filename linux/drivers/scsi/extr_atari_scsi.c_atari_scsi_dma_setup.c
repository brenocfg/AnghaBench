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
struct NCR5380_hostdata {TYPE_1__* host; } ;
struct TYPE_6__ {int dma_mode_status; unsigned long fdc_acces_seccount; } ;
struct TYPE_5__ {int dma_ctrl; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 scalar_t__ IS_A_TT () ; 
 int /*<<< orphan*/  NDEBUG_DMA ; 
 int /*<<< orphan*/  SCSI_DMA_SETADR (unsigned long) ; 
 int /*<<< orphan*/  SCSI_DMA_WRITE_P (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  STRAM_ADDR (unsigned long) ; 
 int atari_dma_active ; 
 int /*<<< orphan*/  atari_dma_buffer ; 
 void* atari_dma_orig_addr ; 
 unsigned long atari_dma_phys_buffer ; 
 unsigned long atari_dma_startaddr ; 
 int /*<<< orphan*/  dma_addr ; 
 int /*<<< orphan*/  dma_cache_maintenance (unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  dma_cnt ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,unsigned long) ; 
 TYPE_3__ st_dma ; 
 TYPE_2__ tt_scsi_dma ; 
 int /*<<< orphan*/  udelay (int) ; 
 unsigned long virt_to_phys (void*) ; 

__attribute__((used)) static unsigned long atari_scsi_dma_setup(struct NCR5380_hostdata *hostdata,
					  void *data, unsigned long count,
					  int dir)
{
	unsigned long addr = virt_to_phys(data);

	dprintk(NDEBUG_DMA, "scsi%d: setting up dma, data = %p, phys = %lx, count = %ld, dir = %d\n",
	        hostdata->host->host_no, data, addr, count, dir);

	if (!IS_A_TT() && !STRAM_ADDR(addr)) {
		/* If we have a non-DMAable address on a Falcon, use the dribble
		 * buffer; 'orig_addr' != 0 in the read case tells the interrupt
		 * handler to copy data from the dribble buffer to the originally
		 * wanted address.
		 */
		if (dir)
			memcpy(atari_dma_buffer, data, count);
		else
			atari_dma_orig_addr = data;
		addr = atari_dma_phys_buffer;
	}

	atari_dma_startaddr = addr;	/* Needed for calculating residual later. */

	/* Cache cleanup stuff: On writes, push any dirty cache out before sending
	 * it to the peripheral. (Must be done before DMA setup, since at least
	 * the ST-DMA begins to fill internal buffers right after setup. For
	 * reads, invalidate any cache, may be altered after DMA without CPU
	 * knowledge.
	 *
	 * ++roman: For the Medusa, there's no need at all for that cache stuff,
	 * because the hardware does bus snooping (fine!).
	 */
	dma_cache_maintenance(addr, count, dir);

	if (IS_A_TT()) {
		tt_scsi_dma.dma_ctrl = dir;
		SCSI_DMA_WRITE_P(dma_addr, addr);
		SCSI_DMA_WRITE_P(dma_cnt, count);
		tt_scsi_dma.dma_ctrl = dir | 2;
	} else { /* ! IS_A_TT */

		/* set address */
		SCSI_DMA_SETADR(addr);

		/* toggle direction bit to clear FIFO and set DMA direction */
		dir <<= 8;
		st_dma.dma_mode_status = 0x90 | dir;
		st_dma.dma_mode_status = 0x90 | (dir ^ 0x100);
		st_dma.dma_mode_status = 0x90 | dir;
		udelay(40);
		/* On writes, round up the transfer length to the next multiple of 512
		 * (see also comment at atari_dma_xfer_len()). */
		st_dma.fdc_acces_seccount = (count + (dir ? 511 : 0)) >> 9;
		udelay(40);
		st_dma.dma_mode_status = 0x10 | dir;
		udelay(40);
		/* need not restore value of dir, only boolean value is tested */
		atari_dma_active = 1;
	}

	return count;
}