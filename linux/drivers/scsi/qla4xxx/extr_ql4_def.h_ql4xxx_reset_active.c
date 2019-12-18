#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scsi_qla_host {int /*<<< orphan*/  dpc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPC_HA_UNRECOVERABLE ; 
 int /*<<< orphan*/  DPC_RESET_ACTIVE ; 
 int /*<<< orphan*/  DPC_RESET_HA ; 
 int /*<<< orphan*/  DPC_RESET_HA_FW_CONTEXT ; 
 int /*<<< orphan*/  DPC_RESET_HA_INTR ; 
 int /*<<< orphan*/  DPC_RETRY_RESET_HA ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ql4xxx_reset_active(struct scsi_qla_host *ha)
{
	return test_bit(DPC_RESET_ACTIVE, &ha->dpc_flags) ||
	       test_bit(DPC_RESET_HA, &ha->dpc_flags) ||
	       test_bit(DPC_RETRY_RESET_HA, &ha->dpc_flags) ||
	       test_bit(DPC_RESET_HA_INTR, &ha->dpc_flags) ||
	       test_bit(DPC_RESET_HA_FW_CONTEXT, &ha->dpc_flags) ||
	       test_bit(DPC_HA_UNRECOVERABLE, &ha->dpc_flags);

}