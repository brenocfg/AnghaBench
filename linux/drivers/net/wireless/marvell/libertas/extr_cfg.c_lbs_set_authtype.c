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
struct lbs_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct cmd_ds_802_11_authenticate {int authtype; int /*<<< orphan*/  bssid; TYPE_1__ hdr; } ;
struct cfg80211_connect_params {int /*<<< orphan*/  auth_type; int /*<<< orphan*/  bssid; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_AUTHENTICATE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int lbs_auth_to_authtype (int /*<<< orphan*/ ) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_authenticate*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_authenticate*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lbs_set_authtype(struct lbs_private *priv,
			    struct cfg80211_connect_params *sme)
{
	struct cmd_ds_802_11_authenticate cmd;
	int ret;

	/*
	 * cmd        11 00
	 * size       19 00
	 * sequence   xx xx
	 * result     00 00
	 * BSS id     00 13 19 80 da 30
	 * auth type  00
	 * reserved   00 00 00 00 00 00 00 00 00 00
	 */
	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	if (sme->bssid)
		memcpy(cmd.bssid, sme->bssid, ETH_ALEN);
	/* convert auth_type */
	ret = lbs_auth_to_authtype(sme->auth_type);
	if (ret < 0)
		goto done;

	cmd.authtype = ret;
	ret = lbs_cmd_with_response(priv, CMD_802_11_AUTHENTICATE, &cmd);

 done:
	return ret;
}