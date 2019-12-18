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
struct lpfc_vport {int /*<<< orphan*/  fc_portname; int /*<<< orphan*/  fc_nodename; } ;
struct TYPE_2__ {int /*<<< orphan*/  wwpn; int /*<<< orphan*/  wwnn; } ;
struct fc_rdp_port_name_desc {void* length; TYPE_1__ port_names; void* tag; } ;

/* Variables and functions */
 int RDP_PORT_NAMES_DESC_TAG ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint32_t
lpfc_rdp_res_diag_port_names(struct fc_rdp_port_name_desc *desc,
		struct lpfc_vport *vport)
{

	desc->tag = cpu_to_be32(RDP_PORT_NAMES_DESC_TAG);

	memcpy(desc->port_names.wwnn, &vport->fc_nodename,
			sizeof(desc->port_names.wwnn));

	memcpy(desc->port_names.wwpn, &vport->fc_portname,
			sizeof(desc->port_names.wwpn));

	desc->length = cpu_to_be32(sizeof(desc->port_names));
	return sizeof(struct fc_rdp_port_name_desc);
}