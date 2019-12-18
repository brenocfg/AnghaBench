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
struct TYPE_2__ {int /*<<< orphan*/  recovery_supported; } ;
struct be_adapter {int priv_flags; int /*<<< orphan*/  flags; TYPE_1__ error_recovery; } ;

/* Variables and functions */
 int BE_DISABLE_TPE_RECOVERY ; 
 int /*<<< orphan*/  BE_FLAGS_TRY_RECOVERY ; 
 int EIO ; 
 int /*<<< orphan*/  be_cleanup (struct be_adapter*) ; 
 int be_fw_wait_ready (struct be_adapter*) ; 
 int be_resume (struct be_adapter*) ; 
 int be_tpe_recover (struct be_adapter*) ; 
 int /*<<< orphan*/  lancer_chip (struct be_adapter*) ; 

__attribute__((used)) static int be_err_recover(struct be_adapter *adapter)
{
	int status;

	if (!lancer_chip(adapter)) {
		if (!adapter->error_recovery.recovery_supported ||
		    adapter->priv_flags & BE_DISABLE_TPE_RECOVERY)
			return -EIO;
		status = be_tpe_recover(adapter);
		if (status)
			goto err;
	}

	/* Wait for adapter to reach quiescent state before
	 * destroying queues
	 */
	status = be_fw_wait_ready(adapter);
	if (status)
		goto err;

	adapter->flags |= BE_FLAGS_TRY_RECOVERY;

	be_cleanup(adapter);

	status = be_resume(adapter);
	if (status)
		goto err;

	adapter->flags &= ~BE_FLAGS_TRY_RECOVERY;

err:
	return status;
}