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
struct mwifiex_ds_auto_ds {int /*<<< orphan*/  auto_ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_AUTO_DS ; 
 int /*<<< orphan*/  DEEP_SLEEP_OFF ; 
 int /*<<< orphan*/  DIS_AUTO_PS ; 
 int /*<<< orphan*/  HostCmd_CMD_802_11_PS_MODE_ENH ; 
 int mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mwifiex_ds_auto_ds*,int) ; 

int mwifiex_disable_auto_ds(struct mwifiex_private *priv)
{
	struct mwifiex_ds_auto_ds auto_ds = {
		.auto_ds = DEEP_SLEEP_OFF,
	};

	return mwifiex_send_cmd(priv, HostCmd_CMD_802_11_PS_MODE_ENH,
				DIS_AUTO_PS, BITMAP_AUTO_DS, &auto_ds, true);
}