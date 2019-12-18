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
typedef  int /*<<< orphan*/  u64 ;
struct tcm_qla2xxx_lport {struct scsi_qla_host* qla_vha; } ;
struct TYPE_4__ {void* target_lport_ptr; } ;
struct scsi_qla_host {TYPE_2__ vha_tgt; struct qla_hw_data* hw; } ;
struct TYPE_3__ {int /*<<< orphan*/ * tgt_ops; } ;
struct qla_hw_data {TYPE_1__ tgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  tcm_qla2xxx_template ; 

__attribute__((used)) static int tcm_qla2xxx_lport_register_cb(struct scsi_qla_host *vha,
					 void *target_lport_ptr,
					 u64 npiv_wwpn, u64 npiv_wwnn)
{
	struct qla_hw_data *ha = vha->hw;
	struct tcm_qla2xxx_lport *lport =
			(struct tcm_qla2xxx_lport *)target_lport_ptr;
	/*
	 * Setup tgt_ops, local pointer to vha and target_lport_ptr
	 */
	ha->tgt.tgt_ops = &tcm_qla2xxx_template;
	vha->vha_tgt.target_lport_ptr = target_lport_ptr;
	lport->qla_vha = vha;

	return 0;
}