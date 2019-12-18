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
struct wmi_set_pcp_channel_cmd {int channel; } ;
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int /*<<< orphan*/  main_ndev; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_SET_PCP_CHANNEL_CMDID ; 
 struct wil6210_vif* ndev_to_vif (int /*<<< orphan*/ ) ; 
 int wmi_send (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmi_set_pcp_channel_cmd*,int) ; 

int wmi_set_channel(struct wil6210_priv *wil, int channel)
{
	struct wil6210_vif *vif = ndev_to_vif(wil->main_ndev);
	struct wmi_set_pcp_channel_cmd cmd = {
		.channel = channel - 1,
	};

	return wmi_send(wil, WMI_SET_PCP_CHANNEL_CMDID, vif->mid,
			&cmd, sizeof(cmd));
}