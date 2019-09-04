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
struct se_cmd {scalar_t__ prot_type; int /*<<< orphan*/  reftag_seed; TYPE_2__* se_dev; } ;
struct TYPE_7__ {int apptag_check_mask; int app_escape; int ref_escape; int ref_remap; int /*<<< orphan*/  ref_tag; int /*<<< orphan*/  pi_interval; int /*<<< orphan*/  bg_type; } ;
struct TYPE_8__ {TYPE_3__ dif; } ;
struct ib_sig_domain {TYPE_4__ sig; int /*<<< orphan*/  sig_type; } ;
struct ib_sig_attrs {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  block_size; } ;
struct TYPE_6__ {TYPE_1__ dev_attrib; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SIG_TYPE_T10_DIF ; 
 int /*<<< orphan*/  IB_T10DIF_CRC ; 
 scalar_t__ TARGET_DIF_TYPE1_PROT ; 
 scalar_t__ TARGET_DIF_TYPE2_PROT ; 

__attribute__((used)) static inline void
isert_set_dif_domain(struct se_cmd *se_cmd, struct ib_sig_attrs *sig_attrs,
		     struct ib_sig_domain *domain)
{
	domain->sig_type = IB_SIG_TYPE_T10_DIF;
	domain->sig.dif.bg_type = IB_T10DIF_CRC;
	domain->sig.dif.pi_interval = se_cmd->se_dev->dev_attrib.block_size;
	domain->sig.dif.ref_tag = se_cmd->reftag_seed;
	/*
	 * At the moment we hard code those, but if in the future
	 * the target core would like to use it, we will take it
	 * from se_cmd.
	 */
	domain->sig.dif.apptag_check_mask = 0xffff;
	domain->sig.dif.app_escape = true;
	domain->sig.dif.ref_escape = true;
	if (se_cmd->prot_type == TARGET_DIF_TYPE1_PROT ||
	    se_cmd->prot_type == TARGET_DIF_TYPE2_PROT)
		domain->sig.dif.ref_remap = true;
}