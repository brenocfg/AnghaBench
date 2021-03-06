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
struct wmi_tkip_micerr_event {int /*<<< orphan*/  is_mcast; int /*<<< orphan*/  key_id; } ;
struct wmi {int dummy; } ;
struct ath6kl_vif {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ath6kl_tkip_micerr_event (struct ath6kl_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_tkip_micerr_event_rx(struct wmi *wmi, u8 *datap, int len,
					   struct ath6kl_vif *vif)
{
	struct wmi_tkip_micerr_event *ev;

	if (len < sizeof(struct wmi_tkip_micerr_event))
		return -EINVAL;

	ev = (struct wmi_tkip_micerr_event *) datap;

	ath6kl_tkip_micerr_event(vif, ev->key_id, ev->is_mcast);

	return 0;
}