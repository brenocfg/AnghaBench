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
struct be_queue_info {scalar_t__ used; scalar_t__ len; int head; } ;
struct TYPE_4__ {struct be_queue_info q; } ;
struct TYPE_6__ {size_t mcc_tag_available; unsigned int* mcc_tag; size_t mcc_alloc_index; int /*<<< orphan*/  mcc_lock; TYPE_2__* ptag_state; scalar_t__* mcc_tag_status; TYPE_1__ mcc_obj; } ;
struct beiscsi_hba {TYPE_3__ ctrl; } ;
struct be_mcc_wrb {unsigned int tag0; } ;
struct TYPE_5__ {int /*<<< orphan*/ * cbfn; scalar_t__ tag_state; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_INIT ; 
 int BEISCSI_LOG_MBOX ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int MAX_MCC_CMD ; 
 int MCC_Q_WRB_IDX_MASK ; 
 int MCC_Q_WRB_IDX_SHIFT ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (struct be_mcc_wrb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_head_inc (struct be_queue_info*) ; 
 struct be_mcc_wrb* queue_head_node (struct be_queue_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct be_mcc_wrb *alloc_mcc_wrb(struct beiscsi_hba *phba,
				 unsigned int *ref_tag)
{
	struct be_queue_info *mccq = &phba->ctrl.mcc_obj.q;
	struct be_mcc_wrb *wrb = NULL;
	unsigned int tag;

	spin_lock(&phba->ctrl.mcc_lock);
	if (mccq->used == mccq->len) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT |
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
			    "BC_%d : MCC queue full: WRB used %u tag avail %u\n",
			    mccq->used, phba->ctrl.mcc_tag_available);
		goto alloc_failed;
	}

	if (!phba->ctrl.mcc_tag_available)
		goto alloc_failed;

	tag = phba->ctrl.mcc_tag[phba->ctrl.mcc_alloc_index];
	if (!tag) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_INIT |
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_MBOX,
			    "BC_%d : MCC tag 0 allocated: tag avail %u alloc index %u\n",
			    phba->ctrl.mcc_tag_available,
			    phba->ctrl.mcc_alloc_index);
		goto alloc_failed;
	}

	/* return this tag for further reference */
	*ref_tag = tag;
	phba->ctrl.mcc_tag[phba->ctrl.mcc_alloc_index] = 0;
	phba->ctrl.mcc_tag_status[tag] = 0;
	phba->ctrl.ptag_state[tag].tag_state = 0;
	phba->ctrl.ptag_state[tag].cbfn = NULL;
	phba->ctrl.mcc_tag_available--;
	if (phba->ctrl.mcc_alloc_index == (MAX_MCC_CMD - 1))
		phba->ctrl.mcc_alloc_index = 0;
	else
		phba->ctrl.mcc_alloc_index++;

	wrb = queue_head_node(mccq);
	memset(wrb, 0, sizeof(*wrb));
	wrb->tag0 = tag;
	wrb->tag0 |= (mccq->head << MCC_Q_WRB_IDX_SHIFT) & MCC_Q_WRB_IDX_MASK;
	queue_head_inc(mccq);
	mccq->used++;

alloc_failed:
	spin_unlock(&phba->ctrl.mcc_lock);
	return wrb;
}