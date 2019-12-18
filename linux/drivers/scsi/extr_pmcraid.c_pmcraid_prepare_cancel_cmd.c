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
struct pmcraid_ioarcb {int /*<<< orphan*/ * cdb; int /*<<< orphan*/  request_type; int /*<<< orphan*/  resource_handle; int /*<<< orphan*/  ioarcb_bus_addr; } ;
struct pmcraid_cmd {TYPE_1__* ioa_cb; } ;
typedef  int /*<<< orphan*/  ioarcb_addr ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_2__ {struct pmcraid_ioarcb ioarcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCRAID_ABORT_CMD ; 
 int /*<<< orphan*/  PMCRAID_MAX_CDB_LEN ; 
 int /*<<< orphan*/  REQ_TYPE_IOACMD ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmcraid_prepare_cancel_cmd(
	struct pmcraid_cmd *cmd,
	struct pmcraid_cmd *cmd_to_cancel
)
{
	struct pmcraid_ioarcb *ioarcb = &cmd->ioa_cb->ioarcb;
	__be64 ioarcb_addr;

	/* IOARCB address of the command to be cancelled is given in
	 * cdb[2]..cdb[9] is Big-Endian format. Note that length bits in
	 * IOARCB address are not masked.
	 */
	ioarcb_addr = cpu_to_be64(le64_to_cpu(cmd_to_cancel->ioa_cb->ioarcb.ioarcb_bus_addr));

	/* Get the resource handle to where the command to be aborted has been
	 * sent.
	 */
	ioarcb->resource_handle = cmd_to_cancel->ioa_cb->ioarcb.resource_handle;
	ioarcb->request_type = REQ_TYPE_IOACMD;
	memset(ioarcb->cdb, 0, PMCRAID_MAX_CDB_LEN);
	ioarcb->cdb[0] = PMCRAID_ABORT_CMD;

	memcpy(&(ioarcb->cdb[2]), &ioarcb_addr, sizeof(ioarcb_addr));
}