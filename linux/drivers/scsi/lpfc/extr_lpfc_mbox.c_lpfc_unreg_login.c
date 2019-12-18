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
typedef  size_t uint16_t ;
struct lpfc_hba {scalar_t__ sli_rev; int /*<<< orphan*/ * vpi_ids; } ;
struct TYPE_8__ {int /*<<< orphan*/  vpi; scalar_t__ rsvd1; int /*<<< orphan*/  rpi; } ;
struct TYPE_9__ {TYPE_1__ varUnregLogin; } ;
struct TYPE_11__ {int /*<<< orphan*/  mbxOwner; int /*<<< orphan*/  mbxCommand; TYPE_2__ un; } ;
struct TYPE_10__ {TYPE_4__ mb; } ;
struct TYPE_12__ {TYPE_3__ u; } ;
typedef  TYPE_4__ MAILBOX_t ;
typedef  TYPE_5__ LPFC_MBOXQ_t ;

/* Variables and functions */
 scalar_t__ LPFC_SLI_REV3 ; 
 int /*<<< orphan*/  MBX_UNREG_LOGIN ; 
 int /*<<< orphan*/  OWN_HOST ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

void
lpfc_unreg_login(struct lpfc_hba *phba, uint16_t vpi, uint32_t rpi,
		 LPFC_MBOXQ_t * pmb)
{
	MAILBOX_t *mb;

	mb = &pmb->u.mb;
	memset(pmb, 0, sizeof (LPFC_MBOXQ_t));

	mb->un.varUnregLogin.rpi = rpi;
	mb->un.varUnregLogin.rsvd1 = 0;
	if (phba->sli_rev >= LPFC_SLI_REV3)
		mb->un.varUnregLogin.vpi = phba->vpi_ids[vpi];

	mb->mbxCommand = MBX_UNREG_LOGIN;
	mb->mbxOwner = OWN_HOST;

	return;
}