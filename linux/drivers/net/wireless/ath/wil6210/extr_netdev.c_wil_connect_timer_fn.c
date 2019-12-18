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
struct wil6210_vif {int /*<<< orphan*/  disconnect_worker; } ;
struct wil6210_priv {int /*<<< orphan*/  wmi_wq; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  connect_timer ; 
 struct wil6210_vif* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct wil6210_vif* vif ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_dbg_wmi (struct wil6210_priv*,char*,int) ; 
 int /*<<< orphan*/  wil_err (struct wil6210_priv*,char*) ; 

__attribute__((used)) static void wil_connect_timer_fn(struct timer_list *t)
{
	struct wil6210_vif *vif = from_timer(vif, t, connect_timer);
	struct wil6210_priv *wil = vif_to_wil(vif);
	bool q;

	wil_err(wil, "Connect timeout detected, disconnect station\n");

	/* reschedule to thread context - disconnect won't
	 * run from atomic context.
	 * queue on wmi_wq to prevent race with connect event.
	 */
	q = queue_work(wil->wmi_wq, &vif->disconnect_worker);
	wil_dbg_wmi(wil, "queue_work of disconnect_worker -> %d\n", q);
}