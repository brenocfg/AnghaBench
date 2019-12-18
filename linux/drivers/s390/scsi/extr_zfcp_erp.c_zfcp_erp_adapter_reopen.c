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
struct zfcp_adapter {int /*<<< orphan*/  erp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_ERP_ACTION_REOPEN_ADAPTER ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zfcp_erp_action_enqueue (int /*<<< orphan*/ ,struct zfcp_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_block (struct zfcp_adapter*,int) ; 
 int /*<<< orphan*/  zfcp_scsi_schedule_rports_block (struct zfcp_adapter*) ; 

void zfcp_erp_adapter_reopen(struct zfcp_adapter *adapter, int clear,
			     char *dbftag)
{
	unsigned long flags;

	zfcp_erp_adapter_block(adapter, clear);
	zfcp_scsi_schedule_rports_block(adapter);

	write_lock_irqsave(&adapter->erp_lock, flags);
	zfcp_erp_action_enqueue(ZFCP_ERP_ACTION_REOPEN_ADAPTER, adapter,
				NULL, NULL, dbftag, 0);
	write_unlock_irqrestore(&adapter->erp_lock, flags);
}