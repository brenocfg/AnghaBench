#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct lpfc_sli_ring {int num_mask; TYPE_2__* prt; } ;
struct lpfc_sli {struct lpfc_sli_ring* sli3_ring; } ;
struct lpfc_hba {struct lpfc_sli sli; } ;
struct TYPE_13__ {int ring; int recvNotify; int numMask; TYPE_3__* rrRegs; scalar_t__ profile; scalar_t__ maxRespXchg; scalar_t__ maxOrigXchg; } ;
struct TYPE_14__ {TYPE_4__ varCfgRing; } ;
struct TYPE_15__ {TYPE_5__ un; int /*<<< orphan*/  mbxOwner; int /*<<< orphan*/  mbxCommand; } ;
struct TYPE_10__ {TYPE_6__ mb; } ;
struct TYPE_16__ {TYPE_1__ u; } ;
struct TYPE_12__ {scalar_t__ rval; int rmask; int tmask; int /*<<< orphan*/  tval; } ;
struct TYPE_11__ {scalar_t__ rctl; int /*<<< orphan*/  type; scalar_t__ profile; } ;
typedef  TYPE_6__ MAILBOX_t ;
typedef  TYPE_7__ LPFC_MBOXQ_t ;

/* Variables and functions */
 scalar_t__ FC_RCTL_ELS_REQ ; 
 int /*<<< orphan*/  MBX_CONFIG_RING ; 
 int /*<<< orphan*/  OWN_HOST ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

void
lpfc_config_ring(struct lpfc_hba * phba, int ring, LPFC_MBOXQ_t * pmb)
{
	int i;
	MAILBOX_t *mb = &pmb->u.mb;
	struct lpfc_sli *psli;
	struct lpfc_sli_ring *pring;

	memset(pmb, 0, sizeof (LPFC_MBOXQ_t));

	mb->un.varCfgRing.ring = ring;
	mb->un.varCfgRing.maxOrigXchg = 0;
	mb->un.varCfgRing.maxRespXchg = 0;
	mb->un.varCfgRing.recvNotify = 1;

	psli = &phba->sli;
	pring = &psli->sli3_ring[ring];
	mb->un.varCfgRing.numMask = pring->num_mask;
	mb->mbxCommand = MBX_CONFIG_RING;
	mb->mbxOwner = OWN_HOST;

	/* Is this ring configured for a specific profile */
	if (pring->prt[0].profile) {
		mb->un.varCfgRing.profile = pring->prt[0].profile;
		return;
	}

	/* Otherwise we setup specific rctl / type masks for this ring */
	for (i = 0; i < pring->num_mask; i++) {
		mb->un.varCfgRing.rrRegs[i].rval = pring->prt[i].rctl;
		if (mb->un.varCfgRing.rrRegs[i].rval != FC_RCTL_ELS_REQ)
			mb->un.varCfgRing.rrRegs[i].rmask = 0xff;
		else
			mb->un.varCfgRing.rrRegs[i].rmask = 0xfe;
		mb->un.varCfgRing.rrRegs[i].tval = pring->prt[i].type;
		mb->un.varCfgRing.rrRegs[i].tmask = 0xff;
	}

	return;
}