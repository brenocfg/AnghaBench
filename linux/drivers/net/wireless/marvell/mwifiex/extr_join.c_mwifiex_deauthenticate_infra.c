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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/ * mac_address; } ;
struct TYPE_4__ {TYPE_1__ bss_descriptor; } ;
struct mwifiex_private {TYPE_2__ curr_bss_params; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_802_11_DEAUTHENTICATE ; 
 scalar_t__ is_zero_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mwifiex_deauthenticate_infra(struct mwifiex_private *priv, u8 *mac)
{
	u8 mac_address[ETH_ALEN];
	int ret;

	if (!mac || is_zero_ether_addr(mac))
		memcpy(mac_address,
		       priv->curr_bss_params.bss_descriptor.mac_address,
		       ETH_ALEN);
	else
		memcpy(mac_address, mac, ETH_ALEN);

	ret = mwifiex_send_cmd(priv, HostCmd_CMD_802_11_DEAUTHENTICATE,
			       HostCmd_ACT_GEN_SET, 0, mac_address, true);

	return ret;
}