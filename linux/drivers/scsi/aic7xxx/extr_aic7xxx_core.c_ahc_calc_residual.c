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
typedef  int uint32_t ;
struct status_pkt {int /*<<< orphan*/  residual_datacnt; int /*<<< orphan*/  residual_sg_ptr; } ;
struct scb {int flags; struct hardware_scb* hscb; } ;
struct TYPE_2__ {struct status_pkt status; } ;
struct hardware_scb {TYPE_1__ shared_data; int /*<<< orphan*/  sgptr; } ;
struct ahc_softc {int dummy; } ;
struct ahc_dma_seg {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int AHC_DMA_LAST_SEG ; 
 int AHC_SG_LEN_MASK ; 
 int AHC_SHOW_MISC ; 
 int SCB_SENSE ; 
 int SG_FULL_RESID ; 
 int SG_LIST_NULL ; 
 int SG_PTR_MASK ; 
 int SG_RESID_VALID ; 
 int ahc_debug ; 
 int ahc_get_transfer_length (struct scb*) ; 
 int ahc_le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_print_path (struct ahc_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahc_set_residual (struct scb*,int) ; 
 int /*<<< orphan*/  ahc_set_sense_residual (struct scb*,int) ; 
 struct ahc_dma_seg* ahc_sg_bus_to_virt (struct scb*,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  printk (char*,char*,int) ; 

__attribute__((used)) static void
ahc_calc_residual(struct ahc_softc *ahc, struct scb *scb)
{
	struct hardware_scb *hscb;
	struct status_pkt *spkt;
	uint32_t sgptr;
	uint32_t resid_sgptr;
	uint32_t resid;

	/*
	 * 5 cases.
	 * 1) No residual.
	 *    SG_RESID_VALID clear in sgptr.
	 * 2) Transferless command
	 * 3) Never performed any transfers.
	 *    sgptr has SG_FULL_RESID set.
	 * 4) No residual but target did not
	 *    save data pointers after the
	 *    last transfer, so sgptr was
	 *    never updated.
	 * 5) We have a partial residual.
	 *    Use residual_sgptr to determine
	 *    where we are.
	 */

	hscb = scb->hscb;
	sgptr = ahc_le32toh(hscb->sgptr);
	if ((sgptr & SG_RESID_VALID) == 0)
		/* Case 1 */
		return;
	sgptr &= ~SG_RESID_VALID;

	if ((sgptr & SG_LIST_NULL) != 0)
		/* Case 2 */
		return;

	spkt = &hscb->shared_data.status;
	resid_sgptr = ahc_le32toh(spkt->residual_sg_ptr);
	if ((sgptr & SG_FULL_RESID) != 0) {
		/* Case 3 */
		resid = ahc_get_transfer_length(scb);
	} else if ((resid_sgptr & SG_LIST_NULL) != 0) {
		/* Case 4 */
		return;
	} else if ((resid_sgptr & ~SG_PTR_MASK) != 0) {
		panic("Bogus resid sgptr value 0x%x\n", resid_sgptr);
	} else {
		struct ahc_dma_seg *sg;

		/*
		 * Remainder of the SG where the transfer
		 * stopped.  
		 */
		resid = ahc_le32toh(spkt->residual_datacnt) & AHC_SG_LEN_MASK;
		sg = ahc_sg_bus_to_virt(scb, resid_sgptr & SG_PTR_MASK);

		/* The residual sg_ptr always points to the next sg */
		sg--;

		/*
		 * Add up the contents of all residual
		 * SG segments that are after the SG where
		 * the transfer stopped.
		 */
		while ((ahc_le32toh(sg->len) & AHC_DMA_LAST_SEG) == 0) {
			sg++;
			resid += ahc_le32toh(sg->len) & AHC_SG_LEN_MASK;
		}
	}
	if ((scb->flags & SCB_SENSE) == 0)
		ahc_set_residual(scb, resid);
	else
		ahc_set_sense_residual(scb, resid);

#ifdef AHC_DEBUG
	if ((ahc_debug & AHC_SHOW_MISC) != 0) {
		ahc_print_path(ahc, scb);
		printk("Handled %sResidual of %d bytes\n",
		       (scb->flags & SCB_SENSE) ? "Sense " : "", resid);
	}
#endif
}