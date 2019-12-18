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
struct wil6210_priv {int /*<<< orphan*/  status; int /*<<< orphan*/  vif_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wil_dbg_pm (struct wil6210_priv*,char*) ; 
 int /*<<< orphan*/  wil_enable_irq (struct wil6210_priv*) ; 
 int wil_has_active_ifaces (struct wil6210_priv*,int,int) ; 
 int /*<<< orphan*/  wil_status_suspended ; 
 int wil_up (struct wil6210_priv*) ; 

__attribute__((used)) static int wil_resume_radio_off(struct wil6210_priv *wil)
{
	int rc = 0;
	bool active_ifaces;

	wil_dbg_pm(wil, "Enabling PCIe IRQ\n");
	wil_enable_irq(wil);
	/* if any netif up, bring hardware up
	 * During open(), IFF_UP set after actual device method
	 * invocation. This prevent recursive call to wil_up()
	 * wil_status_suspended will be cleared in wil_reset
	 */
	mutex_lock(&wil->vif_mutex);
	active_ifaces = wil_has_active_ifaces(wil, true, false);
	mutex_unlock(&wil->vif_mutex);
	if (active_ifaces)
		rc = wil_up(wil);
	else
		clear_bit(wil_status_suspended, wil->status);

	return rc;
}