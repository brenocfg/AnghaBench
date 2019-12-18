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
struct wmi_echo_cmd {int /*<<< orphan*/  value; } ;
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int /*<<< orphan*/  main_ndev; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  WIL_WMI_CALL_GENERAL_TO_MS ; 
 int /*<<< orphan*/  WMI_ECHO_CMDID ; 
 int /*<<< orphan*/  WMI_ECHO_RSP_EVENTID ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 struct wil6210_vif* ndev_to_vif (int /*<<< orphan*/ ) ; 
 int wmi_call (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmi_echo_cmd*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wmi_echo(struct wil6210_priv *wil)
{
	struct wil6210_vif *vif = ndev_to_vif(wil->main_ndev);
	struct wmi_echo_cmd cmd = {
		.value = cpu_to_le32(0x12345678),
	};

	return wmi_call(wil, WMI_ECHO_CMDID, vif->mid, &cmd, sizeof(cmd),
			WMI_ECHO_RSP_EVENTID, NULL, 0,
			WIL_WMI_CALL_GENERAL_TO_MS);
}