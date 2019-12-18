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
typedef  int u8 ;
struct mwifiex_private {TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_cap_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISSUPP_TDLS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ mwifiex_is_tdls_chan_switching (struct mwifiex_private*) ; 
 scalar_t__ mwifiex_is_tdls_off_chan (struct mwifiex_private*) ; 

u8 mwifiex_is_send_cmd_allowed(struct mwifiex_private *priv)
{
	if (!priv || !ISSUPP_TDLS_ENABLED(priv->adapter->fw_cap_info))
		return true;

	if (mwifiex_is_tdls_chan_switching(priv) ||
	    mwifiex_is_tdls_off_chan(priv))
		return false;

	return true;
}