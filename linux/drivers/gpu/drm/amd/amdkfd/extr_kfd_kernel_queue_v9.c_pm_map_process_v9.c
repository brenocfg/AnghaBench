#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct qcm_process_device {int page_table_base; int gds_size; int tba_addr; int tma_addr; int gds_context_area; int /*<<< orphan*/  sh_mem_bases; int /*<<< orphan*/  sh_mem_config; int /*<<< orphan*/  queue_count; scalar_t__ is_debug; int /*<<< orphan*/  num_oac; int /*<<< orphan*/  num_gws; TYPE_4__* pqm; } ;
struct TYPE_10__ {int gds_size; int gds_size_hi; int sdma_enable; int /*<<< orphan*/  num_queues; int /*<<< orphan*/  num_oac; int /*<<< orphan*/  num_gws; } ;
struct TYPE_7__ {int diq_enable; int process_quantum; int /*<<< orphan*/  pasid; } ;
struct TYPE_6__ {int /*<<< orphan*/  u32All; } ;
struct pm4_mes_map_process {void* vm_context_page_table_base_addr_hi32; void* vm_context_page_table_base_addr_lo32; void* gds_addr_hi; void* gds_addr_lo; void* sq_shader_tma_hi; void* sq_shader_tma_lo; void* sq_shader_tba_hi; void* sq_shader_tba_lo; int /*<<< orphan*/  sh_mem_bases; int /*<<< orphan*/  sh_mem_config; TYPE_5__ bitfields14; TYPE_2__ bitfields2; TYPE_1__ header; } ;
struct packet_manager {int dummy; } ;
struct TYPE_9__ {TYPE_3__* process; } ;
struct TYPE_8__ {int /*<<< orphan*/  pasid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IT_MAP_PROCESS ; 
 void* lower_32_bits (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_build_pm4_header (int /*<<< orphan*/ ,int) ; 
 void* upper_32_bits (int) ; 

__attribute__((used)) static int pm_map_process_v9(struct packet_manager *pm,
		uint32_t *buffer, struct qcm_process_device *qpd)
{
	struct pm4_mes_map_process *packet;
	uint64_t vm_page_table_base_addr = qpd->page_table_base;

	packet = (struct pm4_mes_map_process *)buffer;
	memset(buffer, 0, sizeof(struct pm4_mes_map_process));

	packet->header.u32All = pm_build_pm4_header(IT_MAP_PROCESS,
					sizeof(struct pm4_mes_map_process));
	packet->bitfields2.diq_enable = (qpd->is_debug) ? 1 : 0;
	packet->bitfields2.process_quantum = 1;
	packet->bitfields2.pasid = qpd->pqm->process->pasid;
	packet->bitfields14.gds_size = qpd->gds_size & 0x3F;
	packet->bitfields14.gds_size_hi = (qpd->gds_size >> 6) & 0xF;
	packet->bitfields14.num_gws = qpd->num_gws;
	packet->bitfields14.num_oac = qpd->num_oac;
	packet->bitfields14.sdma_enable = 1;
	packet->bitfields14.num_queues = (qpd->is_debug) ? 0 : qpd->queue_count;

	packet->sh_mem_config = qpd->sh_mem_config;
	packet->sh_mem_bases = qpd->sh_mem_bases;
	packet->sq_shader_tba_lo = lower_32_bits(qpd->tba_addr >> 8);
	packet->sq_shader_tba_hi = upper_32_bits(qpd->tba_addr >> 8);
	packet->sq_shader_tma_lo = lower_32_bits(qpd->tma_addr >> 8);
	packet->sq_shader_tma_hi = upper_32_bits(qpd->tma_addr >> 8);

	packet->gds_addr_lo = lower_32_bits(qpd->gds_context_area);
	packet->gds_addr_hi = upper_32_bits(qpd->gds_context_area);

	packet->vm_context_page_table_base_addr_lo32 =
			lower_32_bits(vm_page_table_base_addr);
	packet->vm_context_page_table_base_addr_hi32 =
			upper_32_bits(vm_page_table_base_addr);

	return 0;
}