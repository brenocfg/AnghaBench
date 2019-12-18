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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  hw_value; } ;
struct wil_p2p_info {int /*<<< orphan*/  listen_duration; int /*<<< orphan*/  discovery_timer; int /*<<< orphan*/  discovery_expired_work; TYPE_1__ listen_chan; } ;
struct wil6210_vif {struct wil_p2p_info p2p; } ;
struct wil6210_priv {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P2P_DEFAULT_BI ; 
 int /*<<< orphan*/  P2P_WILDCARD_SSID ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_p2p_listen_expired ; 
 int wmi_p2p_cfg (struct wil6210_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wmi_set_ssid (struct wil6210_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wmi_start_listen (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wmi_stop_discovery (struct wil6210_vif*) ; 

__attribute__((used)) static int wil_p2p_start_listen(struct wil6210_vif *vif)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	struct wil_p2p_info *p2p = &vif->p2p;
	u8 channel = p2p->listen_chan.hw_value;
	int rc;

	lockdep_assert_held(&wil->mutex);

	rc = wmi_p2p_cfg(vif, channel, P2P_DEFAULT_BI);
	if (rc) {
		wil_err(wil, "wmi_p2p_cfg failed\n");
		goto out;
	}

	rc = wmi_set_ssid(vif, strlen(P2P_WILDCARD_SSID), P2P_WILDCARD_SSID);
	if (rc) {
		wil_err(wil, "wmi_set_ssid failed\n");
		goto out_stop;
	}

	rc = wmi_start_listen(vif);
	if (rc) {
		wil_err(wil, "wmi_start_listen failed\n");
		goto out_stop;
	}

	INIT_WORK(&p2p->discovery_expired_work, wil_p2p_listen_expired);
	mod_timer(&p2p->discovery_timer,
		  jiffies + msecs_to_jiffies(p2p->listen_duration));
out_stop:
	if (rc)
		wmi_stop_discovery(vif);

out:
	return rc;
}