#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {scalar_t__ area; scalar_t__ domain; scalar_t__ al_pa; } ;
struct TYPE_11__ {TYPE_4__ b; } ;
struct scsi_qla_host {TYPE_2__* hw; TYPE_3__ d_id; } ;
struct TYPE_13__ {scalar_t__ area; scalar_t__ domain; scalar_t__ al_pa; } ;
typedef  TYPE_5__ be_id_t ;
struct TYPE_14__ {int /*<<< orphan*/  b24; } ;
struct TYPE_9__ {int /*<<< orphan*/  host_map; } ;
struct TYPE_10__ {TYPE_1__ tgt; } ;

/* Variables and functions */
 TYPE_7__ be_to_port_id (TYPE_5__) ; 
 struct scsi_qla_host* btree_lookup32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (scalar_t__,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ql_dbg_tgt_mgt ; 
 scalar_t__ ql_dbg_verbose ; 

__attribute__((used)) static inline
struct scsi_qla_host *qlt_find_host_by_d_id(struct scsi_qla_host *vha,
					    be_id_t d_id)
{
	struct scsi_qla_host *host;
	uint32_t key;

	if (vha->d_id.b.area == d_id.area &&
	    vha->d_id.b.domain == d_id.domain &&
	    vha->d_id.b.al_pa == d_id.al_pa)
		return vha;

	key = be_to_port_id(d_id).b24;

	host = btree_lookup32(&vha->hw->tgt.host_map, key);
	if (!host)
		ql_dbg(ql_dbg_tgt_mgt + ql_dbg_verbose, vha, 0xf005,
		    "Unable to find host %06x\n", key);

	return host;
}