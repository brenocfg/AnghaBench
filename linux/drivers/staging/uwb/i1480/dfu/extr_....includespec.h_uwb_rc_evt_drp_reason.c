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
struct uwb_rc_evt_drp {int reason; } ;
typedef  enum uwb_drp_notif_reason { ____Placeholder_uwb_drp_notif_reason } uwb_drp_notif_reason ;

/* Variables and functions */

__attribute__((used)) static inline enum uwb_drp_notif_reason uwb_rc_evt_drp_reason(struct uwb_rc_evt_drp *evt)
{
	return evt->reason & 0x0f;
}