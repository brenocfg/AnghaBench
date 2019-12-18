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
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIL_WMI_CALL_GENERAL_TO_MS ; 
 int /*<<< orphan*/  WMI_DISCOVERY_STOPPED_EVENTID ; 
 int /*<<< orphan*/  WMI_DISCOVERY_STOP_CMDID ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_dbg_wmi (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 int wmi_call (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wmi_stop_discovery(struct wil6210_vif *vif)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	int rc;

	wil_dbg_wmi(wil, "sending WMI_DISCOVERY_STOP_CMDID\n");

	rc = wmi_call(wil, WMI_DISCOVERY_STOP_CMDID, vif->mid, NULL, 0,
		      WMI_DISCOVERY_STOPPED_EVENTID, NULL, 0,
		      WIL_WMI_CALL_GENERAL_TO_MS);

	if (rc)
		wil_err(wil, "Failed to stop discovery\n");

	return rc;
}