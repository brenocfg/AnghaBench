#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* uint16_t ;
struct lpfc_hba {int dummy; } ;
struct TYPE_9__ {int cv; int word_cnt; scalar_t__ resp_offset; scalar_t__ co; void* region_id; void* entry_index; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {TYPE_2__ varDmp; } ;
struct TYPE_11__ {int /*<<< orphan*/  mbxOwner; TYPE_3__ un; int /*<<< orphan*/  mbxCommand; } ;
struct TYPE_8__ {TYPE_4__ mb; } ;
struct TYPE_12__ {void* ctx_buf; TYPE_1__ u; } ;
typedef  TYPE_4__ MAILBOX_t ;
typedef  TYPE_5__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMP_NV_PARAMS ; 
 int DMP_RSP_SIZE ; 
 int /*<<< orphan*/  MBX_DUMP_MEMORY ; 
 int /*<<< orphan*/  OWN_HOST ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

void
lpfc_dump_mem(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb, uint16_t offset,
		uint16_t region_id)
{
	MAILBOX_t *mb;
	void *ctx;

	mb = &pmb->u.mb;
	ctx = pmb->ctx_buf;

	/* Setup to dump VPD region */
	memset(pmb, 0, sizeof (LPFC_MBOXQ_t));
	mb->mbxCommand = MBX_DUMP_MEMORY;
	mb->un.varDmp.cv = 1;
	mb->un.varDmp.type = DMP_NV_PARAMS;
	mb->un.varDmp.entry_index = offset;
	mb->un.varDmp.region_id = region_id;
	mb->un.varDmp.word_cnt = (DMP_RSP_SIZE / sizeof (uint32_t));
	mb->un.varDmp.co = 0;
	mb->un.varDmp.resp_offset = 0;
	pmb->ctx_buf = ctx;
	mb->mbxOwner = OWN_HOST;
	return;
}