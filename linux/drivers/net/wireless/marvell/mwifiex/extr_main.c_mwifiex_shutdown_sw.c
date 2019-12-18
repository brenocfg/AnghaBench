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
struct mwifiex_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* down_dev ) (struct mwifiex_adapter*) ;} ;
struct mwifiex_adapter {TYPE_1__ if_ops; int /*<<< orphan*/  fw_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWIFIEX_BSS_ROLE_ANY ; 
 int /*<<< orphan*/  mwifiex_deauthenticate (struct mwifiex_private*,int /*<<< orphan*/ *) ; 
 struct mwifiex_private* mwifiex_get_priv (struct mwifiex_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_uninit_sw (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mwifiex_adapter*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ ) ; 

int mwifiex_shutdown_sw(struct mwifiex_adapter *adapter)
{
	struct mwifiex_private *priv;

	if (!adapter)
		return 0;

	wait_for_completion(adapter->fw_done);
	/* Caller should ensure we aren't suspending while this happens */
	reinit_completion(adapter->fw_done);

	priv = mwifiex_get_priv(adapter, MWIFIEX_BSS_ROLE_ANY);
	mwifiex_deauthenticate(priv, NULL);

	mwifiex_uninit_sw(adapter);

	if (adapter->if_ops.down_dev)
		adapter->if_ops.down_dev(adapter);

	return 0;
}