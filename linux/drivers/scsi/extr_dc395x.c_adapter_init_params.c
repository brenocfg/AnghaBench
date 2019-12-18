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
struct NvRamType {int max_tag; int channel_cfg; int scsi_id; } ;
struct AdapterCtlBlk {int srb_count; int tag_max_num; int gmode2; int lun_chk; int scan_devices; int hostid_bit; int /*<<< orphan*/  srb_free_list; TYPE_2__* srb_array; scalar_t__ msg_len; scalar_t__* dcb_map; TYPE_1__* scsi_host; scalar_t__ config; scalar_t__ acb_flag; int /*<<< orphan*/  sel_timeout; int /*<<< orphan*/  selto_timer; int /*<<< orphan*/  waiting_timer; int /*<<< orphan*/  srb; int /*<<< orphan*/ * tmp_srb; int /*<<< orphan*/ * active_dcb; int /*<<< orphan*/ * dcb_run_robin; int /*<<< orphan*/  dcb_list; struct NvRamType eeprom; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
struct TYPE_3__ {int this_id; } ;

/* Variables and functions */
 int DC395x_MAX_SCSI_ID ; 
 int DC395x_MAX_SRB_CNT ; 
 int /*<<< orphan*/  DC395x_SEL_TIMEOUT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NAC_SCANLUN ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * waiting_timeout ; 

__attribute__((used)) static void adapter_init_params(struct AdapterCtlBlk *acb)
{
	struct NvRamType *eeprom = &acb->eeprom;
	int i;

	/* NOTE: acb->scsi_host is set at scsi_host/acb creation time */
	/* NOTE: acb->io_port_base is set at port registration time */
	/* NOTE: acb->io_port_len is set at port registration time */

	INIT_LIST_HEAD(&acb->dcb_list);
	acb->dcb_run_robin = NULL;
	acb->active_dcb = NULL;

	INIT_LIST_HEAD(&acb->srb_free_list);
	/*  temp SRB for Q tag used or abort command used  */
	acb->tmp_srb = &acb->srb;
	timer_setup(&acb->waiting_timer, waiting_timeout, 0);
	timer_setup(&acb->selto_timer, NULL, 0);

	acb->srb_count = DC395x_MAX_SRB_CNT;

	acb->sel_timeout = DC395x_SEL_TIMEOUT;	/* timeout=250ms */
	/* NOTE: acb->irq_level is set at IRQ registration time */

	acb->tag_max_num = 1 << eeprom->max_tag;
	if (acb->tag_max_num > 30)
		acb->tag_max_num = 30;

	acb->acb_flag = 0;	/* RESET_DETECT, RESET_DONE, RESET_DEV */
	acb->gmode2 = eeprom->channel_cfg;
	acb->config = 0;	/* NOTE: actually set in adapter_init_chip */

	if (eeprom->channel_cfg & NAC_SCANLUN)
		acb->lun_chk = 1;
	acb->scan_devices = 1;

	acb->scsi_host->this_id = eeprom->scsi_id;
	acb->hostid_bit = (1 << acb->scsi_host->this_id);

	for (i = 0; i < DC395x_MAX_SCSI_ID; i++)
		acb->dcb_map[i] = 0;

	acb->msg_len = 0;
	
	/* link static array of srbs into the srb free list */
	for (i = 0; i < acb->srb_count - 1; i++)
		list_add_tail(&acb->srb_array[i].list, &acb->srb_free_list);
}