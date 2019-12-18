#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mwifiex_private {int dummy; } ;
struct host_cmd_ds_wakeup_reason {int /*<<< orphan*/  wakeup_reason; } ;
struct TYPE_3__ {int /*<<< orphan*/  wakeup_reason; } ;
struct TYPE_4__ {TYPE_1__ hs_wakeup_reason; } ;
struct host_cmd_ds_command {TYPE_2__ params; } ;

/* Variables and functions */

int mwifiex_ret_wakeup_reason(struct mwifiex_private *priv,
			      struct host_cmd_ds_command *resp,
			      struct host_cmd_ds_wakeup_reason *wakeup_reason)
{
	wakeup_reason->wakeup_reason =
		resp->params.hs_wakeup_reason.wakeup_reason;

	return 0;
}