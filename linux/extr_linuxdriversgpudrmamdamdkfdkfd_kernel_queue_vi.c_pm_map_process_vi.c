#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct qcm_process_device {int /*<<< orphan*/  gds_context_area; int /*<<< orphan*/  sh_hidden_private_base; int /*<<< orphan*/  sh_mem_ape1_limit; int /*<<< orphan*/  sh_mem_ape1_base; int /*<<< orphan*/  sh_mem_bases; int /*<<< orphan*/  sh_mem_config; int /*<<< orphan*/  queue_count; scalar_t__ is_debug; int /*<<< orphan*/  num_oac; int /*<<< orphan*/  num_gws; int /*<<< orphan*/  gds_size; int /*<<< orphan*/  page_table_base; TYPE_4__* pqm; } ;
struct TYPE_12__ {int /*<<< orphan*/  num_queues; int /*<<< orphan*/  num_oac; int /*<<< orphan*/  num_gws; int /*<<< orphan*/  gds_size; } ;
struct TYPE_11__ {int /*<<< orphan*/  page_table_base; } ;
struct TYPE_8__ {int diq_enable; int process_quantum; int /*<<< orphan*/  pasid; } ;
struct TYPE_7__ {int /*<<< orphan*/  u32All; } ;
struct pm4_mes_map_process {int /*<<< orphan*/  gds_addr_hi; int /*<<< orphan*/  gds_addr_lo; int /*<<< orphan*/  sh_hidden_private_base_vmid; int /*<<< orphan*/  sh_mem_ape1_limit; int /*<<< orphan*/  sh_mem_ape1_base; int /*<<< orphan*/  sh_mem_bases; int /*<<< orphan*/  sh_mem_config; TYPE_6__ bitfields10; TYPE_5__ bitfields3; TYPE_2__ bitfields2; TYPE_1__ header; } ;
struct packet_manager {int dummy; } ;
struct TYPE_10__ {TYPE_3__* process; } ;
struct TYPE_9__ {int /*<<< orphan*/  pasid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IT_MAP_PROCESS ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_build_pm4_header (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm_map_process_vi(struct packet_manager *pm, uint32_t *buffer,
				struct qcm_process_device *qpd)
{
	struct pm4_mes_map_process *packet;

	packet = (struct pm4_mes_map_process *)buffer;

	memset(buffer, 0, sizeof(struct pm4_mes_map_process));

	packet->header.u32All = pm_build_pm4_header(IT_MAP_PROCESS,
					sizeof(struct pm4_mes_map_process));
	packet->bitfields2.diq_enable = (qpd->is_debug) ? 1 : 0;
	packet->bitfields2.process_quantum = 1;
	packet->bitfields2.pasid = qpd->pqm->process->pasid;
	packet->bitfields3.page_table_base = qpd->page_table_base;
	packet->bitfields10.gds_size = qpd->gds_size;
	packet->bitfields10.num_gws = qpd->num_gws;
	packet->bitfields10.num_oac = qpd->num_oac;
	packet->bitfields10.num_queues = (qpd->is_debug) ? 0 : qpd->queue_count;

	packet->sh_mem_config = qpd->sh_mem_config;
	packet->sh_mem_bases = qpd->sh_mem_bases;
	packet->sh_mem_ape1_base = qpd->sh_mem_ape1_base;
	packet->sh_mem_ape1_limit = qpd->sh_mem_ape1_limit;

	packet->sh_hidden_private_base_vmid = qpd->sh_hidden_private_base;

	packet->gds_addr_lo = lower_32_bits(qpd->gds_context_area);
	packet->gds_addr_hi = upper_32_bits(qpd->gds_context_area);

	return 0;
}