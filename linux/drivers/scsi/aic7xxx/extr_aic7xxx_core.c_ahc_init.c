#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int u_int ;
struct target_cmd {scalar_t__ cmd_valid; } ;
struct scb {int dummy; } ;
struct hardware_scb {int dummy; } ;
struct ahc_tmode_tstate {scalar_t__ ultraenb; } ;
struct ahc_softc {int flags; int features; int our_id; int our_id_b; int unit; int user_discenable; int user_tagenable; int (* bus_chip_init ) (struct ahc_softc*) ;TYPE_1__* scb_data; int /*<<< orphan*/  init_level; int /*<<< orphan*/ * qoutfifo; int /*<<< orphan*/ * qinfifo; struct target_cmd* targetcmds; scalar_t__ shared_data_busaddr; scalar_t__ dma_bug_buf; int /*<<< orphan*/  shared_data_dmamap; int /*<<< orphan*/  shared_data_dmat; int /*<<< orphan*/  parent_dmat; } ;
struct TYPE_9__ {int protocol_version; int transport_version; } ;
struct TYPE_8__ {int protocol_version; int transport_version; } ;
struct TYPE_7__ {scalar_t__ period; int protocol_version; int transport_version; void* width; void* offset; int /*<<< orphan*/  ppr_options; } ;
struct ahc_initiator_tinfo {TYPE_4__ curr; TYPE_3__ goal; TYPE_2__ user; } ;
struct ahc_dma_seg {int dummy; } ;
struct TYPE_10__ {scalar_t__ period; } ;
struct TYPE_6__ {scalar_t__ maxhscbs; } ;

/* Variables and functions */
 int AHC_DEBUG_SEQUENCER ; 
 int AHC_DT ; 
 int AHC_EXTENDED_TRANS_A ; 
 int AHC_EXTENDED_TRANS_B ; 
 int AHC_INITIATORROLE ; 
 int AHC_MORE_SRAM ; 
 int AHC_PAGESCBS ; 
 int AHC_RESET_BUS_A ; 
 int AHC_RESET_BUS_B ; 
 scalar_t__ AHC_SCB_MAX_ALLOC ; 
 int AHC_SEQUENCER_DEBUG ; 
 int AHC_SHOW_MISC ; 
 int AHC_SYNCRATE_DT ; 
 int AHC_SYNCRATE_FAST ; 
 int AHC_SYNCRATE_ULTRA ; 
 int AHC_SYNCRATE_ULTRA2 ; 
 int AHC_TARGETMODE ; 
 int AHC_TERM_ENB_A ; 
 int AHC_TERM_ENB_B ; 
 int AHC_TMODE_CMDS ; 
 int AHC_TMODE_ENABLE ; 
 int AHC_TWIN ; 
 int AHC_ULTRA ; 
 int AHC_ULTRA2 ; 
 int AHC_USEDEFAULTS ; 
 int AHC_WIDE ; 
 int ALL_TARGETS_MASK ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 scalar_t__ BUS_SPACE_MAXADDR_32BIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXSIZE_32BIT ; 
 int /*<<< orphan*/  CLRBRKADRINT ; 
 int /*<<< orphan*/  CLRINT ; 
 int /*<<< orphan*/  CLRPARERR ; 
 int DISC_DSB ; 
 int ENOMEM ; 
 void* MAX_OFFSET ; 
 int MAX_OFFSET_ULTRA2 ; 
 int /*<<< orphan*/  MSG_EXT_PPR_DT_REQ ; 
 void* MSG_EXT_WDTR_BUS_16_BIT ; 
 int RESET_SCSI ; 
 int SCSICONF ; 
 int SOFS ; 
 int SXFR ; 
 int SXFR_ULTRA2 ; 
 int TARG_OFFSET ; 
 int TARG_SCSIRATE ; 
 int ULTRA_ENB ; 
 int WIDEXFER ; 
 int /*<<< orphan*/ * ahc_alloc_tstate (struct ahc_softc*,int,char) ; 
 int ahc_debug ; 
 scalar_t__ ahc_dma_tag_create (struct ahc_softc*,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahc_dmamap_cb ; 
 int /*<<< orphan*/  ahc_dmamap_load (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ahc_dmamem_alloc (struct ahc_softc*,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ahc_initiator_tinfo* ahc_fetch_transinfo (struct ahc_softc*,char,int,int,struct ahc_tmode_tstate**) ; 
 void* ahc_find_period (struct ahc_softc*,int,int) ; 
 int ahc_inb (struct ahc_softc*,int) ; 
 scalar_t__ ahc_init_scbdata (struct ahc_softc*) ; 
 int ahc_name (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_sync_tqinfifo (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ahc_syncrates ; 
 int /*<<< orphan*/  memset (struct ahc_initiator_tinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int stub1 (struct ahc_softc*) ; 

int
ahc_init(struct ahc_softc *ahc)
{
	int	 max_targ;
	u_int	 i;
	u_int	 scsi_conf;
	u_int	 ultraenb;
	u_int	 discenable;
	u_int	 tagenable;
	size_t	 driver_data_size;

#ifdef AHC_DEBUG
	if ((ahc_debug & AHC_DEBUG_SEQUENCER) != 0)
		ahc->flags |= AHC_SEQUENCER_DEBUG;
#endif

#ifdef AHC_PRINT_SRAM
	printk("Scratch Ram:");
	for (i = 0x20; i < 0x5f; i++) {
		if (((i % 8) == 0) && (i != 0)) {
			printk ("\n              ");
		}
		printk (" 0x%x", ahc_inb(ahc, i));
	}
	if ((ahc->features & AHC_MORE_SRAM) != 0) {
		for (i = 0x70; i < 0x7f; i++) {
			if (((i % 8) == 0) && (i != 0)) {
				printk ("\n              ");
			}
			printk (" 0x%x", ahc_inb(ahc, i));
		}
	}
	printk ("\n");
	/*
	 * Reading uninitialized scratch ram may
	 * generate parity errors.
	 */
	ahc_outb(ahc, CLRINT, CLRPARERR);
	ahc_outb(ahc, CLRINT, CLRBRKADRINT);
#endif
	max_targ = 15;

	/*
	 * Assume we have a board at this stage and it has been reset.
	 */
	if ((ahc->flags & AHC_USEDEFAULTS) != 0)
		ahc->our_id = ahc->our_id_b = 7;
	
	/*
	 * Default to allowing initiator operations.
	 */
	ahc->flags |= AHC_INITIATORROLE;

	/*
	 * Only allow target mode features if this unit has them enabled.
	 */
	if ((AHC_TMODE_ENABLE & (0x1 << ahc->unit)) == 0)
		ahc->features &= ~AHC_TARGETMODE;

	ahc->init_level++;

	/*
	 * DMA tag for our command fifos and other data in system memory
	 * the card's sequencer must be able to access.  For initiator
	 * roles, we need to allocate space for the qinfifo and qoutfifo.
	 * The qinfifo and qoutfifo are composed of 256 1 byte elements. 
	 * When providing for the target mode role, we must additionally
	 * provide space for the incoming target command fifo and an extra
	 * byte to deal with a dma bug in some chip versions.
	 */
	driver_data_size = 2 * 256 * sizeof(uint8_t);
	if ((ahc->features & AHC_TARGETMODE) != 0)
		driver_data_size += AHC_TMODE_CMDS * sizeof(struct target_cmd)
				 + /*DMA WideOdd Bug Buffer*/1;
	if (ahc_dma_tag_create(ahc, ahc->parent_dmat, /*alignment*/1,
			       /*boundary*/BUS_SPACE_MAXADDR_32BIT + 1,
			       /*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
			       /*highaddr*/BUS_SPACE_MAXADDR,
			       /*filter*/NULL, /*filterarg*/NULL,
			       driver_data_size,
			       /*nsegments*/1,
			       /*maxsegsz*/BUS_SPACE_MAXSIZE_32BIT,
			       /*flags*/0, &ahc->shared_data_dmat) != 0) {
		return (ENOMEM);
	}

	ahc->init_level++;

	/* Allocation of driver data */
	if (ahc_dmamem_alloc(ahc, ahc->shared_data_dmat,
			     (void **)&ahc->qoutfifo,
			     BUS_DMA_NOWAIT, &ahc->shared_data_dmamap) != 0) {
		return (ENOMEM);
	}

	ahc->init_level++;

	/* And permanently map it in */
	ahc_dmamap_load(ahc, ahc->shared_data_dmat, ahc->shared_data_dmamap,
			ahc->qoutfifo, driver_data_size, ahc_dmamap_cb,
			&ahc->shared_data_busaddr, /*flags*/0);

	if ((ahc->features & AHC_TARGETMODE) != 0) {
		ahc->targetcmds = (struct target_cmd *)ahc->qoutfifo;
		ahc->qoutfifo = (uint8_t *)&ahc->targetcmds[AHC_TMODE_CMDS];
		ahc->dma_bug_buf = ahc->shared_data_busaddr
				 + driver_data_size - 1;
		/* All target command blocks start out invalid. */
		for (i = 0; i < AHC_TMODE_CMDS; i++)
			ahc->targetcmds[i].cmd_valid = 0;
		ahc_sync_tqinfifo(ahc, BUS_DMASYNC_PREREAD);
		ahc->qoutfifo = (uint8_t *)&ahc->targetcmds[256];
	}
	ahc->qinfifo = &ahc->qoutfifo[256];

	ahc->init_level++;

	/* Allocate SCB data now that buffer_dmat is initialized */
	if (ahc->scb_data->maxhscbs == 0)
		if (ahc_init_scbdata(ahc) != 0)
			return (ENOMEM);

	/*
	 * Allocate a tstate to house information for our
	 * initiator presence on the bus as well as the user
	 * data for any target mode initiator.
	 */
	if (ahc_alloc_tstate(ahc, ahc->our_id, 'A') == NULL) {
		printk("%s: unable to allocate ahc_tmode_tstate.  "
		       "Failing attach\n", ahc_name(ahc));
		return (ENOMEM);
	}

	if ((ahc->features & AHC_TWIN) != 0) {
		if (ahc_alloc_tstate(ahc, ahc->our_id_b, 'B') == NULL) {
			printk("%s: unable to allocate ahc_tmode_tstate.  "
			       "Failing attach\n", ahc_name(ahc));
			return (ENOMEM);
		}
	}

	if (ahc->scb_data->maxhscbs < AHC_SCB_MAX_ALLOC) {
		ahc->flags |= AHC_PAGESCBS;
	} else {
		ahc->flags &= ~AHC_PAGESCBS;
	}

#ifdef AHC_DEBUG
	if (ahc_debug & AHC_SHOW_MISC) {
		printk("%s: hardware scb %u bytes; kernel scb %u bytes; "
		       "ahc_dma %u bytes\n",
			ahc_name(ahc),
			(u_int)sizeof(struct hardware_scb),
			(u_int)sizeof(struct scb),
			(u_int)sizeof(struct ahc_dma_seg));
	}
#endif /* AHC_DEBUG */

	/*
	 * Look at the information that board initialization or
	 * the board bios has left us.
	 */
	if (ahc->features & AHC_TWIN) {
		scsi_conf = ahc_inb(ahc, SCSICONF + 1);
		if ((scsi_conf & RESET_SCSI) != 0
		 && (ahc->flags & AHC_INITIATORROLE) != 0)
			ahc->flags |= AHC_RESET_BUS_B;
	}

	scsi_conf = ahc_inb(ahc, SCSICONF);
	if ((scsi_conf & RESET_SCSI) != 0
	 && (ahc->flags & AHC_INITIATORROLE) != 0)
		ahc->flags |= AHC_RESET_BUS_A;

	ultraenb = 0;	
	tagenable = ALL_TARGETS_MASK;

	/* Grab the disconnection disable table and invert it for our needs */
	if ((ahc->flags & AHC_USEDEFAULTS) != 0) {
		printk("%s: Host Adapter Bios disabled.  Using default SCSI "
			"device parameters\n", ahc_name(ahc));
		ahc->flags |= AHC_EXTENDED_TRANS_A|AHC_EXTENDED_TRANS_B|
			      AHC_TERM_ENB_A|AHC_TERM_ENB_B;
		discenable = ALL_TARGETS_MASK;
		if ((ahc->features & AHC_ULTRA) != 0)
			ultraenb = ALL_TARGETS_MASK;
	} else {
		discenable = ~((ahc_inb(ahc, DISC_DSB + 1) << 8)
			   | ahc_inb(ahc, DISC_DSB));
		if ((ahc->features & (AHC_ULTRA|AHC_ULTRA2)) != 0)
			ultraenb = (ahc_inb(ahc, ULTRA_ENB + 1) << 8)
				      | ahc_inb(ahc, ULTRA_ENB);
	}

	if ((ahc->features & (AHC_WIDE|AHC_TWIN)) == 0)
		max_targ = 7;

	for (i = 0; i <= max_targ; i++) {
		struct ahc_initiator_tinfo *tinfo;
		struct ahc_tmode_tstate *tstate;
		u_int our_id;
		u_int target_id;
		char channel;

		channel = 'A';
		our_id = ahc->our_id;
		target_id = i;
		if (i > 7 && (ahc->features & AHC_TWIN) != 0) {
			channel = 'B';
			our_id = ahc->our_id_b;
			target_id = i % 8;
		}
		tinfo = ahc_fetch_transinfo(ahc, channel, our_id,
					    target_id, &tstate);
		/* Default to async narrow across the board */
		memset(tinfo, 0, sizeof(*tinfo));
		if (ahc->flags & AHC_USEDEFAULTS) {
			if ((ahc->features & AHC_WIDE) != 0)
				tinfo->user.width = MSG_EXT_WDTR_BUS_16_BIT;

			/*
			 * These will be truncated when we determine the
			 * connection type we have with the target.
			 */
			tinfo->user.period = ahc_syncrates->period;
			tinfo->user.offset = MAX_OFFSET;
		} else {
			u_int scsirate;
			uint16_t mask;

			/* Take the settings leftover in scratch RAM. */
			scsirate = ahc_inb(ahc, TARG_SCSIRATE + i);
			mask = (0x01 << i);
			if ((ahc->features & AHC_ULTRA2) != 0) {
				u_int offset;
				u_int maxsync;

				if ((scsirate & SOFS) == 0x0F) {
					/*
					 * Haven't negotiated yet,
					 * so the format is different.
					 */
					scsirate = (scsirate & SXFR) >> 4
						 | (ultraenb & mask)
						  ? 0x08 : 0x0
						 | (scsirate & WIDEXFER);
					offset = MAX_OFFSET_ULTRA2;
				} else
					offset = ahc_inb(ahc, TARG_OFFSET + i);
				if ((scsirate & ~WIDEXFER) == 0 && offset != 0)
					/* Set to the lowest sync rate, 5MHz */
					scsirate |= 0x1c;
				maxsync = AHC_SYNCRATE_ULTRA2;
				if ((ahc->features & AHC_DT) != 0)
					maxsync = AHC_SYNCRATE_DT;
				tinfo->user.period =
				    ahc_find_period(ahc, scsirate, maxsync);
				if (offset == 0)
					tinfo->user.period = 0;
				else
					tinfo->user.offset = MAX_OFFSET;
				if ((scsirate & SXFR_ULTRA2) <= 8/*10MHz*/
				 && (ahc->features & AHC_DT) != 0)
					tinfo->user.ppr_options =
					    MSG_EXT_PPR_DT_REQ;
			} else if ((scsirate & SOFS) != 0) {
				if ((scsirate & SXFR) == 0x40
				 && (ultraenb & mask) != 0) {
					/* Treat 10MHz as a non-ultra speed */
					scsirate &= ~SXFR;
				 	ultraenb &= ~mask;
				}
				tinfo->user.period = 
				    ahc_find_period(ahc, scsirate,
						    (ultraenb & mask)
						   ? AHC_SYNCRATE_ULTRA
						   : AHC_SYNCRATE_FAST);
				if (tinfo->user.period != 0)
					tinfo->user.offset = MAX_OFFSET;
			}
			if (tinfo->user.period == 0)
				tinfo->user.offset = 0;
			if ((scsirate & WIDEXFER) != 0
			 && (ahc->features & AHC_WIDE) != 0)
				tinfo->user.width = MSG_EXT_WDTR_BUS_16_BIT;
			tinfo->user.protocol_version = 4;
			if ((ahc->features & AHC_DT) != 0)
				tinfo->user.transport_version = 3;
			else
				tinfo->user.transport_version = 2;
			tinfo->goal.protocol_version = 2;
			tinfo->goal.transport_version = 2;
			tinfo->curr.protocol_version = 2;
			tinfo->curr.transport_version = 2;
		}
		tstate->ultraenb = 0;
	}
	ahc->user_discenable = discenable;
	ahc->user_tagenable = tagenable;

	return (ahc->bus_chip_init(ahc));
}