#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  command_id; } ;
struct TYPE_8__ {TYPE_1__ basic_io; } ;
struct TYPE_9__ {int /*<<< orphan*/  scb_busaddr; TYPE_2__ cmd; int /*<<< orphan*/  lun; int /*<<< orphan*/  target_id; int /*<<< orphan*/  bus; int /*<<< orphan*/ * cdb; scalar_t__ scsi_cmd; } ;
typedef  TYPE_3__ ips_scb_t ;
struct TYPE_10__ {scalar_t__ mem_ptr; int /*<<< orphan*/  host_num; } ;
typedef  TYPE_4__ ips_ha_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_VAR (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ IPS_REG_I2O_INMSGQ ; 
 int IPS_SUCCESS ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  ips_name ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
ips_issue_i2o_memio(ips_ha_t * ha, ips_scb_t * scb)
{

	METHOD_TRACE("ips_issue_i2o_memio", 1);

	if (scb->scsi_cmd) {
		DEBUG_VAR(2, "(%s%d) ips_issue: cmd 0x%X id %d (%d %d %d)",
			  ips_name,
			  ha->host_num,
			  scb->cdb[0],
			  scb->cmd.basic_io.command_id,
			  scb->bus, scb->target_id, scb->lun);
	} else {
		DEBUG_VAR(2, "(%s%d) ips_issue: logical cmd id %d",
			  ips_name, ha->host_num, scb->cmd.basic_io.command_id);
	}

	writel(scb->scb_busaddr, ha->mem_ptr + IPS_REG_I2O_INMSGQ);

	return (IPS_SUCCESS);
}