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
struct mwifiex_private {int /*<<< orphan*/  adapter; } ;
struct host_cmd_ds_command {scalar_t__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HostCmd_RESULT_OK ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mwifiex_ret_cfg_data(struct mwifiex_private *priv,
				struct host_cmd_ds_command *resp)
{
	if (resp->result != HostCmd_RESULT_OK) {
		mwifiex_dbg(priv->adapter, ERROR, "Cal data cmd resp failed\n");
		return -1;
	}

	return 0;
}