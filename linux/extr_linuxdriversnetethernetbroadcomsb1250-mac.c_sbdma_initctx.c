#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sbmacdma {int sbdma_channel; int sbdma_txdir; int sbdma_maxdescr; void* sbdma_ctxtable; struct sbdmadscr* sbdma_dscrtable; int /*<<< orphan*/  sbdma_dscrtable_phys; struct sbdmadscr* sbdma_dscrtable_end; void* sbdma_dscrtable_unaligned; int /*<<< orphan*/ * sbdma_oodpktlost; int /*<<< orphan*/ * sbdma_curdscr; int /*<<< orphan*/ * sbdma_dscrcnt; int /*<<< orphan*/ * sbdma_dscrbase; int /*<<< orphan*/ * sbdma_config1; int /*<<< orphan*/ * sbdma_config0; struct sbmac_softc* sbdma_eth; } ;
struct sbmac_softc {int /*<<< orphan*/ * sbm_base; } ;
struct sbdmadscr {int dummy; } ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  R_MAC_DMA_CONFIG0 ; 
 int /*<<< orphan*/  R_MAC_DMA_CONFIG1 ; 
 int /*<<< orphan*/  R_MAC_DMA_CUR_DSCRADDR ; 
 int /*<<< orphan*/  R_MAC_DMA_DSCR_BASE ; 
 int /*<<< orphan*/  R_MAC_DMA_DSCR_CNT ; 
 int /*<<< orphan*/  R_MAC_DMA_OODPKTLOST_RX ; 
 int R_MAC_DMA_REGISTER (int,int,int /*<<< orphan*/ ) ; 
 int R_MAC_RMON_COLLISIONS ; 
 int R_MAC_RMON_EX_COL ; 
 int R_MAC_RMON_FCS_ERROR ; 
 int R_MAC_RMON_LATE_COL ; 
 int R_MAC_RMON_RX_ALIGN_ERROR ; 
 int R_MAC_RMON_RX_BAD ; 
 int R_MAC_RMON_RX_BCAST ; 
 int R_MAC_RMON_RX_BYTES ; 
 int R_MAC_RMON_RX_CODE_ERROR ; 
 int R_MAC_RMON_RX_FCS_ERROR ; 
 int R_MAC_RMON_RX_GOOD ; 
 int R_MAC_RMON_RX_LENGTH_ERROR ; 
 int R_MAC_RMON_RX_MCAST ; 
 int R_MAC_RMON_RX_OVERSIZE ; 
 int R_MAC_RMON_RX_RUNT ; 
 int R_MAC_RMON_TX_ABORT ; 
 int R_MAC_RMON_TX_BAD ; 
 int R_MAC_RMON_TX_BYTES ; 
 int R_MAC_RMON_TX_GOOD ; 
 int R_MAC_RMON_TX_OVERSIZE ; 
 int R_MAC_RMON_TX_RUNT ; 
 int /*<<< orphan*/  __raw_writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (struct sbdmadscr*) ; 

__attribute__((used)) static void sbdma_initctx(struct sbmacdma *d, struct sbmac_softc *s, int chan,
			  int txrx, int maxdescr)
{
#ifdef CONFIG_SBMAC_COALESCE
	int int_pktcnt, int_timeout;
#endif

	/*
	 * Save away interesting stuff in the structure
	 */

	d->sbdma_eth       = s;
	d->sbdma_channel   = chan;
	d->sbdma_txdir     = txrx;

#if 0
	/* RMON clearing */
	s->sbe_idx =(s->sbm_base - A_MAC_BASE_0)/MAC_SPACING;
#endif

	__raw_writeq(0, s->sbm_base + R_MAC_RMON_TX_BYTES);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_COLLISIONS);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_LATE_COL);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_EX_COL);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_FCS_ERROR);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_TX_ABORT);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_TX_BAD);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_TX_GOOD);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_TX_RUNT);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_TX_OVERSIZE);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_RX_BYTES);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_RX_MCAST);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_RX_BCAST);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_RX_BAD);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_RX_GOOD);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_RX_RUNT);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_RX_OVERSIZE);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_RX_FCS_ERROR);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_RX_LENGTH_ERROR);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_RX_CODE_ERROR);
	__raw_writeq(0, s->sbm_base + R_MAC_RMON_RX_ALIGN_ERROR);

	/*
	 * initialize register pointers
	 */

	d->sbdma_config0 =
		s->sbm_base + R_MAC_DMA_REGISTER(txrx,chan,R_MAC_DMA_CONFIG0);
	d->sbdma_config1 =
		s->sbm_base + R_MAC_DMA_REGISTER(txrx,chan,R_MAC_DMA_CONFIG1);
	d->sbdma_dscrbase =
		s->sbm_base + R_MAC_DMA_REGISTER(txrx,chan,R_MAC_DMA_DSCR_BASE);
	d->sbdma_dscrcnt =
		s->sbm_base + R_MAC_DMA_REGISTER(txrx,chan,R_MAC_DMA_DSCR_CNT);
	d->sbdma_curdscr =
		s->sbm_base + R_MAC_DMA_REGISTER(txrx,chan,R_MAC_DMA_CUR_DSCRADDR);
	if (d->sbdma_txdir)
		d->sbdma_oodpktlost = NULL;
	else
		d->sbdma_oodpktlost =
			s->sbm_base + R_MAC_DMA_REGISTER(txrx,chan,R_MAC_DMA_OODPKTLOST_RX);

	/*
	 * Allocate memory for the ring
	 */

	d->sbdma_maxdescr = maxdescr;

	d->sbdma_dscrtable_unaligned = kcalloc(d->sbdma_maxdescr + 1,
					       sizeof(*d->sbdma_dscrtable),
					       GFP_KERNEL);

	/*
	 * The descriptor table must be aligned to at least 16 bytes or the
	 * MAC will corrupt it.
	 */
	d->sbdma_dscrtable = (struct sbdmadscr *)
			     ALIGN((unsigned long)d->sbdma_dscrtable_unaligned,
				   sizeof(*d->sbdma_dscrtable));

	d->sbdma_dscrtable_end = d->sbdma_dscrtable + d->sbdma_maxdescr;

	d->sbdma_dscrtable_phys = virt_to_phys(d->sbdma_dscrtable);

	/*
	 * And context table
	 */

	d->sbdma_ctxtable = kcalloc(d->sbdma_maxdescr,
				    sizeof(*d->sbdma_ctxtable), GFP_KERNEL);

#ifdef CONFIG_SBMAC_COALESCE
	/*
	 * Setup Rx/Tx DMA coalescing defaults
	 */

	int_pktcnt = (txrx == DMA_TX) ? int_pktcnt_tx : int_pktcnt_rx;
	if ( int_pktcnt ) {
		d->sbdma_int_pktcnt = int_pktcnt;
	} else {
		d->sbdma_int_pktcnt = 1;
	}

	int_timeout = (txrx == DMA_TX) ? int_timeout_tx : int_timeout_rx;
	if ( int_timeout ) {
		d->sbdma_int_timeout = int_timeout;
	} else {
		d->sbdma_int_timeout = 0;
	}
#endif

}