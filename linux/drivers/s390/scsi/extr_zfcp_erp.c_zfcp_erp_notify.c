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
struct zfcp_erp_action {unsigned long status; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  erp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ zfcp_erp_action_is_running (struct zfcp_erp_action*) ; 
 int /*<<< orphan*/  zfcp_erp_action_ready (struct zfcp_erp_action*) ; 

void zfcp_erp_notify(struct zfcp_erp_action *erp_action, unsigned long set_mask)
{
	struct zfcp_adapter *adapter = erp_action->adapter;
	unsigned long flags;

	write_lock_irqsave(&adapter->erp_lock, flags);
	if (zfcp_erp_action_is_running(erp_action)) {
		erp_action->status |= set_mask;
		zfcp_erp_action_ready(erp_action);
	}
	write_unlock_irqrestore(&adapter->erp_lock, flags);
}