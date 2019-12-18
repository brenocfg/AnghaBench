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
typedef  int /*<<< orphan*/  u8 ;
struct wmi_scan_complete_event {int /*<<< orphan*/  status; } ;
struct wmi {int is_probe_ssid; } ;
struct ath6kl_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_sle32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_scan_complete_evt (struct ath6kl_vif*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_scan_complete_rx(struct wmi *wmi, u8 *datap, int len,
				       struct ath6kl_vif *vif)
{
	struct wmi_scan_complete_event *ev;

	ev = (struct wmi_scan_complete_event *) datap;

	ath6kl_scan_complete_evt(vif, a_sle32_to_cpu(ev->status));
	wmi->is_probe_ssid = false;

	return 0;
}