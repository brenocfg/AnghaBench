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
struct scsi_cmnd {int prot_flags; int /*<<< orphan*/  request; } ;
struct TYPE_4__ {int apptag_check_mask; int app_escape; int ref_escape; int ref_remap; int /*<<< orphan*/  ref_tag; int /*<<< orphan*/  pi_interval; } ;
struct TYPE_3__ {TYPE_2__ dif; } ;
struct ib_sig_domain {TYPE_1__ sig; int /*<<< orphan*/  sig_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SIG_TYPE_T10_DIF ; 
 int SCSI_PROT_REF_INCREMENT ; 
 int /*<<< orphan*/  scsi_prot_interval (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  t10_pi_ref_tag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iser_set_dif_domain(struct scsi_cmnd *sc, struct ib_sig_domain *domain)
{
	domain->sig_type = IB_SIG_TYPE_T10_DIF;
	domain->sig.dif.pi_interval = scsi_prot_interval(sc);
	domain->sig.dif.ref_tag = t10_pi_ref_tag(sc->request);
	/*
	 * At the moment we hard code those, but in the future
	 * we will take them from sc.
	 */
	domain->sig.dif.apptag_check_mask = 0xffff;
	domain->sig.dif.app_escape = true;
	domain->sig.dif.ref_escape = true;
	if (sc->prot_flags & SCSI_PROT_REF_INCREMENT)
		domain->sig.dif.ref_remap = true;
}