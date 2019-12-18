#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int els_req; } ;
struct fc_rdp_link_service_desc {void* length; TYPE_1__ payload; void* tag; } ;

/* Variables and functions */
 int RDP_LINK_SERVICE_DESC_TAG ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static uint32_t
lpfc_rdp_res_link_service(struct fc_rdp_link_service_desc *desc,
		uint32_t word0)
{

	desc->tag = cpu_to_be32(RDP_LINK_SERVICE_DESC_TAG);
	desc->payload.els_req = word0;
	desc->length = cpu_to_be32(sizeof(desc->payload));

	return sizeof(struct fc_rdp_link_service_desc);
}