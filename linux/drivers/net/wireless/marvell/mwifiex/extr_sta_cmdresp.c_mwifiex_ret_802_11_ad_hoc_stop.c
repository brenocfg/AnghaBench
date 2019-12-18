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
struct mwifiex_private {int dummy; } ;
struct host_cmd_ds_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  mwifiex_reset_connect_state (struct mwifiex_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mwifiex_ret_802_11_ad_hoc_stop(struct mwifiex_private *priv,
					  struct host_cmd_ds_command *resp)
{
	mwifiex_reset_connect_state(priv, WLAN_REASON_DEAUTH_LEAVING, false);
	return 0;
}