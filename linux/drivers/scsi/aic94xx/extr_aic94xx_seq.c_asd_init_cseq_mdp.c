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
typedef  int u16 ;
struct TYPE_6__ {scalar_t__ dma_handle; } ;
struct TYPE_8__ {TYPE_3__* actual_dl; TYPE_2__ next_scb; } ;
struct TYPE_5__ {scalar_t__ max_ddbs; } ;
struct asd_ha_struct {TYPE_4__ seq; TYPE_1__ hw_prof; } ;
struct TYPE_7__ {scalar_t__ dma_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_BUSADDR_LO (scalar_t__) ; 
 int /*<<< orphan*/  ASD_DEF_DL_TOGGLE ; 
 int /*<<< orphan*/  ASD_DPRINTK (char*,unsigned long long) ; 
 scalar_t__ CSEQ_CLEAR_LU_HEAD ; 
 scalar_t__ CSEQ_EMPTY_TRANS_CTX ; 
 scalar_t__ CSEQ_FIRST_INV_DDB_SITE ; 
 scalar_t__ CSEQ_FIRST_INV_SCB_SITE ; 
 scalar_t__ CSEQ_GLOBAL_HEAD ; 
 scalar_t__ CSEQ_GLOBAL_PREV_SCB ; 
 int /*<<< orphan*/  CSEQ_HQ_DONE_BASE ; 
 scalar_t__ CSEQ_HQ_DONE_PASS ; 
 scalar_t__ CSEQ_HQ_DONE_POINTER ; 
 int /*<<< orphan*/  CSEQ_HQ_NEW_POINTER ; 
 scalar_t__ CSEQ_HSB_SITE ; 
 scalar_t__ CSEQ_LRM_SAVE_SCBPTR ; 
 scalar_t__ CSEQ_LRM_SAVE_SCRPAGE ; 
 scalar_t__ CSEQ_LRM_SAVE_SINDEX ; 
 scalar_t__ CSEQ_LUN_TO_CHECK ; 
 scalar_t__ CSEQ_LUN_TO_CLEAR ; 
 int CSEQ_PAGE_SIZE ; 
 scalar_t__ CSEQ_Q_LINK_HEAD ; 
 scalar_t__ CSEQ_Q_LINK_TAIL ; 
 scalar_t__ CSEQ_RESP_LEN ; 
 scalar_t__ CSEQ_RET_ADDR ; 
 scalar_t__ CSEQ_RET_SCBPTR ; 
 scalar_t__ CSEQ_SAVE_SCBPTR ; 
 scalar_t__ CSEQ_SCRATCH_FLAGS ; 
 scalar_t__ CSEQ_TMF_OPCODE ; 
 scalar_t__ CSEQ_TMF_SCBPTR ; 
 int /*<<< orphan*/  asd_write_reg_addr (struct asd_ha_struct*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  asd_write_reg_byte (struct asd_ha_struct*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_dword (struct asd_ha_struct*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asd_write_reg_word (struct asd_ha_struct*,scalar_t__,int) ; 
 scalar_t__ last_scb_site_no ; 

__attribute__((used)) static void asd_init_cseq_mdp(struct asd_ha_struct *asd_ha)
{
	int	i;
	int	moffs;

	moffs = CSEQ_PAGE_SIZE * 2;

	/* CSEQ Mode dependent, modes 0-7, page 0 setup. */
	for (i = 0; i < 8; i++) {
		asd_write_reg_word(asd_ha, i*moffs+CSEQ_LRM_SAVE_SINDEX, 0);
		asd_write_reg_word(asd_ha, i*moffs+CSEQ_LRM_SAVE_SCBPTR, 0);
		asd_write_reg_word(asd_ha, i*moffs+CSEQ_Q_LINK_HEAD, 0xFFFF);
		asd_write_reg_word(asd_ha, i*moffs+CSEQ_Q_LINK_TAIL, 0xFFFF);
		asd_write_reg_byte(asd_ha, i*moffs+CSEQ_LRM_SAVE_SCRPAGE, 0);
	}

	/* CSEQ Mode dependent, mode 0-7, page 1 and 2 shall be ignored. */

	/* CSEQ Mode dependent, mode 8, page 0 setup. */
	asd_write_reg_word(asd_ha, CSEQ_RET_ADDR, 0xFFFF);
	asd_write_reg_word(asd_ha, CSEQ_RET_SCBPTR, 0);
	asd_write_reg_word(asd_ha, CSEQ_SAVE_SCBPTR, 0);
	asd_write_reg_word(asd_ha, CSEQ_EMPTY_TRANS_CTX, 0);
	asd_write_reg_word(asd_ha, CSEQ_RESP_LEN, 0);
	asd_write_reg_word(asd_ha, CSEQ_TMF_SCBPTR, 0);
	asd_write_reg_word(asd_ha, CSEQ_GLOBAL_PREV_SCB, 0);
	asd_write_reg_word(asd_ha, CSEQ_GLOBAL_HEAD, 0);
	asd_write_reg_word(asd_ha, CSEQ_CLEAR_LU_HEAD, 0);
	asd_write_reg_byte(asd_ha, CSEQ_TMF_OPCODE, 0);
	asd_write_reg_byte(asd_ha, CSEQ_SCRATCH_FLAGS, 0);
	asd_write_reg_word(asd_ha, CSEQ_HSB_SITE, 0);
	asd_write_reg_word(asd_ha, CSEQ_FIRST_INV_SCB_SITE,
			   (u16)last_scb_site_no+1);
	asd_write_reg_word(asd_ha, CSEQ_FIRST_INV_DDB_SITE,
			   (u16)asd_ha->hw_prof.max_ddbs);

	/* CSEQ Mode dependent, mode 8, page 1 setup. */
	asd_write_reg_dword(asd_ha, CSEQ_LUN_TO_CLEAR, 0);
	asd_write_reg_dword(asd_ha, CSEQ_LUN_TO_CLEAR + 4, 0);
	asd_write_reg_dword(asd_ha, CSEQ_LUN_TO_CHECK, 0);
	asd_write_reg_dword(asd_ha, CSEQ_LUN_TO_CHECK + 4, 0);

	/* CSEQ Mode dependent, mode 8, page 2 setup. */
	/* Tell the sequencer the bus address of the first SCB. */
	asd_write_reg_addr(asd_ha, CSEQ_HQ_NEW_POINTER,
			   asd_ha->seq.next_scb.dma_handle);
	ASD_DPRINTK("First SCB dma_handle: 0x%llx\n",
		    (unsigned long long)asd_ha->seq.next_scb.dma_handle);

	/* Tell the sequencer the first Done List entry address. */
	asd_write_reg_addr(asd_ha, CSEQ_HQ_DONE_BASE,
			   asd_ha->seq.actual_dl->dma_handle);

	/* Initialize the Q_DONE_POINTER with the least significant
	 * 4 bytes of the first Done List address. */
	asd_write_reg_dword(asd_ha, CSEQ_HQ_DONE_POINTER,
			    ASD_BUSADDR_LO(asd_ha->seq.actual_dl->dma_handle));

	asd_write_reg_byte(asd_ha, CSEQ_HQ_DONE_PASS, ASD_DEF_DL_TOGGLE);

	/* CSEQ Mode dependent, mode 8, page 3 shall be ignored. */
}