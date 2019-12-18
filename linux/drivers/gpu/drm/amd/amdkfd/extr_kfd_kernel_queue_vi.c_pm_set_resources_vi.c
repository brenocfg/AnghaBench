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
typedef  int /*<<< orphan*/  uint32_t ;
struct scheduling_resources {int /*<<< orphan*/  queue_mask; int /*<<< orphan*/  gws_mask; int /*<<< orphan*/  gds_heap_size; int /*<<< orphan*/  gds_heap_base; int /*<<< orphan*/  oac_mask; int /*<<< orphan*/  vmid_mask; } ;
struct TYPE_8__ {int /*<<< orphan*/  gds_heap_size; int /*<<< orphan*/  gds_heap_base; } ;
struct TYPE_7__ {int /*<<< orphan*/  oac_mask; } ;
struct TYPE_6__ {int unmap_latency; int /*<<< orphan*/  vmid_mask; int /*<<< orphan*/  queue_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  u32All; } ;
struct pm4_mes_set_resources {void* queue_mask_hi; void* queue_mask_lo; void* gws_mask_hi; void* gws_mask_lo; TYPE_4__ bitfields8; TYPE_3__ bitfields7; TYPE_2__ bitfields2; TYPE_1__ header; } ;
struct packet_manager {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IT_SET_RESOURCES ; 
 int KFD_UNMAP_LATENCY_MS ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_build_pm4_header (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_type__mes_set_resources__hsa_interface_queue_hiq ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

int pm_set_resources_vi(struct packet_manager *pm, uint32_t *buffer,
				struct scheduling_resources *res)
{
	struct pm4_mes_set_resources *packet;

	packet = (struct pm4_mes_set_resources *)buffer;
	memset(buffer, 0, sizeof(struct pm4_mes_set_resources));

	packet->header.u32All = pm_build_pm4_header(IT_SET_RESOURCES,
					sizeof(struct pm4_mes_set_resources));

	packet->bitfields2.queue_type =
			queue_type__mes_set_resources__hsa_interface_queue_hiq;
	packet->bitfields2.vmid_mask = res->vmid_mask;
	packet->bitfields2.unmap_latency = KFD_UNMAP_LATENCY_MS / 100;
	packet->bitfields7.oac_mask = res->oac_mask;
	packet->bitfields8.gds_heap_base = res->gds_heap_base;
	packet->bitfields8.gds_heap_size = res->gds_heap_size;

	packet->gws_mask_lo = lower_32_bits(res->gws_mask);
	packet->gws_mask_hi = upper_32_bits(res->gws_mask);

	packet->queue_mask_lo = lower_32_bits(res->queue_mask);
	packet->queue_mask_hi = upper_32_bits(res->queue_mask);

	return 0;
}