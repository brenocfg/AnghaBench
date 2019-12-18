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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {int /*<<< orphan*/  cfg_tgt_queue_depth; int /*<<< orphan*/  phba; } ;
struct TYPE_4__ {int /*<<< orphan*/  evt_listp; } ;
struct TYPE_3__ {int /*<<< orphan*/  evt_listp; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_defer_did; int /*<<< orphan*/  cmd_qdepth; int /*<<< orphan*/  cmd_pending; int /*<<< orphan*/  kref; int /*<<< orphan*/  nlp_fc4_type; int /*<<< orphan*/  nlp_sid; int /*<<< orphan*/  phba; struct lpfc_vport* vport; int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  nlp_delayfunc; TYPE_2__ dev_loss_evt; TYPE_1__ els_retry_evt; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NLP_EVT_NOTHING_PENDING ; 
 int /*<<< orphan*/  NLP_FC4_NONE ; 
 int /*<<< orphan*/  NLP_INT_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_NO_SID ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_els_retry_delay ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
lpfc_initialize_node(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
	uint32_t did)
{
	INIT_LIST_HEAD(&ndlp->els_retry_evt.evt_listp);
	INIT_LIST_HEAD(&ndlp->dev_loss_evt.evt_listp);
	timer_setup(&ndlp->nlp_delayfunc, lpfc_els_retry_delay, 0);
	ndlp->nlp_DID = did;
	ndlp->vport = vport;
	ndlp->phba = vport->phba;
	ndlp->nlp_sid = NLP_NO_SID;
	ndlp->nlp_fc4_type = NLP_FC4_NONE;
	kref_init(&ndlp->kref);
	NLP_INT_NODE_ACT(ndlp);
	atomic_set(&ndlp->cmd_pending, 0);
	ndlp->cmd_qdepth = vport->cfg_tgt_queue_depth;
	ndlp->nlp_defer_did = NLP_EVT_NOTHING_PENDING;
}