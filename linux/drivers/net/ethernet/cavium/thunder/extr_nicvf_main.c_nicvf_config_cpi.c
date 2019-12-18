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
struct TYPE_3__ {int /*<<< orphan*/  rq_cnt; int /*<<< orphan*/  cpi_alg; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ cpi_cfg; } ;
struct nicvf {TYPE_2__* qs; int /*<<< orphan*/  cpi_alg; int /*<<< orphan*/  vf_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  rq_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_MBOX_MSG_CPI_CFG ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static void nicvf_config_cpi(struct nicvf *nic)
{
	union nic_mbx mbx = {};

	mbx.cpi_cfg.msg = NIC_MBOX_MSG_CPI_CFG;
	mbx.cpi_cfg.vf_id = nic->vf_id;
	mbx.cpi_cfg.cpi_alg = nic->cpi_alg;
	mbx.cpi_cfg.rq_cnt = nic->qs->rq_cnt;

	nicvf_send_msg_to_pf(nic, &mbx);
}