#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  fcp_prio_enabled; } ;
struct qla_hw_data {TYPE_2__* fcp_prio_cfg; TYPE_1__ flags; } ;
struct qla_fcp_prio_entry {int flags; int src_pid; int dst_pid; int tag; int /*<<< orphan*/  dst_wwpn; int /*<<< orphan*/  src_wwpn; } ;
struct TYPE_11__ {int b24; } ;
struct TYPE_13__ {int /*<<< orphan*/  port_name; TYPE_3__ d_id; struct qla_hw_data* hw; } ;
typedef  TYPE_5__ scsi_qla_host_t ;
struct TYPE_12__ {int b24; } ;
struct TYPE_14__ {int /*<<< orphan*/  port_name; TYPE_4__ d_id; } ;
typedef  TYPE_6__ fc_port_t ;
struct TYPE_10__ {int num_entries; struct qla_fcp_prio_entry* entry; } ;

/* Variables and functions */
 int FCP_PRIO_ENTRY_DPID_VALID ; 
 int FCP_PRIO_ENTRY_DWWN_VALID ; 
 int FCP_PRIO_ENTRY_SPID_VALID ; 
 int FCP_PRIO_ENTRY_SWWN_VALID ; 
 int FCP_PRIO_ENTRY_TAG_VALID ; 
 int FCP_PRIO_ENTRY_VALID ; 
 int INVALID_PORT_ID ; 
 scalar_t__ wwn_to_u64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla24xx_get_fcp_prio(scsi_qla_host_t *vha, fc_port_t *fcport)
{
	int i, entries;
	uint8_t pid_match, wwn_match;
	int priority;
	uint32_t pid1, pid2;
	uint64_t wwn1, wwn2;
	struct qla_fcp_prio_entry *pri_entry;
	struct qla_hw_data *ha = vha->hw;

	if (!ha->fcp_prio_cfg || !ha->flags.fcp_prio_enabled)
		return -1;

	priority = -1;
	entries = ha->fcp_prio_cfg->num_entries;
	pri_entry = &ha->fcp_prio_cfg->entry[0];

	for (i = 0; i < entries; i++) {
		pid_match = wwn_match = 0;

		if (!(pri_entry->flags & FCP_PRIO_ENTRY_VALID)) {
			pri_entry++;
			continue;
		}

		/* check source pid for a match */
		if (pri_entry->flags & FCP_PRIO_ENTRY_SPID_VALID) {
			pid1 = pri_entry->src_pid & INVALID_PORT_ID;
			pid2 = vha->d_id.b24 & INVALID_PORT_ID;
			if (pid1 == INVALID_PORT_ID)
				pid_match++;
			else if (pid1 == pid2)
				pid_match++;
		}

		/* check destination pid for a match */
		if (pri_entry->flags & FCP_PRIO_ENTRY_DPID_VALID) {
			pid1 = pri_entry->dst_pid & INVALID_PORT_ID;
			pid2 = fcport->d_id.b24 & INVALID_PORT_ID;
			if (pid1 == INVALID_PORT_ID)
				pid_match++;
			else if (pid1 == pid2)
				pid_match++;
		}

		/* check source WWN for a match */
		if (pri_entry->flags & FCP_PRIO_ENTRY_SWWN_VALID) {
			wwn1 = wwn_to_u64(vha->port_name);
			wwn2 = wwn_to_u64(pri_entry->src_wwpn);
			if (wwn2 == (uint64_t)-1)
				wwn_match++;
			else if (wwn1 == wwn2)
				wwn_match++;
		}

		/* check destination WWN for a match */
		if (pri_entry->flags & FCP_PRIO_ENTRY_DWWN_VALID) {
			wwn1 = wwn_to_u64(fcport->port_name);
			wwn2 = wwn_to_u64(pri_entry->dst_wwpn);
			if (wwn2 == (uint64_t)-1)
				wwn_match++;
			else if (wwn1 == wwn2)
				wwn_match++;
		}

		if (pid_match == 2 || wwn_match == 2) {
			/* Found a matching entry */
			if (pri_entry->flags & FCP_PRIO_ENTRY_TAG_VALID)
				priority = pri_entry->tag;
			break;
		}

		pri_entry++;
	}

	return priority;
}