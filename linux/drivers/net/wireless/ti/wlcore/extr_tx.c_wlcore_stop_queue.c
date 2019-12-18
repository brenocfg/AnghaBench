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
struct wl12xx_vif {int dummy; } ;
struct wl1271 {int /*<<< orphan*/  wl_lock; } ;
typedef  enum wlcore_queue_stop_reason { ____Placeholder_wlcore_queue_stop_reason } wlcore_queue_stop_reason ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wlcore_stop_queue_locked (struct wl1271*,struct wl12xx_vif*,int /*<<< orphan*/ ,int) ; 

void wlcore_stop_queue(struct wl1271 *wl, struct wl12xx_vif *wlvif, u8 queue,
		       enum wlcore_queue_stop_reason reason)
{
	unsigned long flags;

	spin_lock_irqsave(&wl->wl_lock, flags);
	wlcore_stop_queue_locked(wl, wlvif, queue, reason);
	spin_unlock_irqrestore(&wl->wl_lock, flags);
}