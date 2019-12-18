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
struct TYPE_2__ {int /*<<< orphan*/ * pbc; } ;
struct ar9170 {int registered; int /*<<< orphan*/  hw; int /*<<< orphan*/  restart_work; TYPE_1__ wps; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carl9170_cancel_worker (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_debugfs_unregister (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_led_unregister (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_unregister_hwrng (struct ar9170*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 

void carl9170_unregister(struct ar9170 *ar)
{
	if (!ar->registered)
		return;

	ar->registered = false;

#ifdef CONFIG_CARL9170_LEDS
	carl9170_led_unregister(ar);
#endif /* CONFIG_CARL9170_LEDS */

#ifdef CONFIG_CARL9170_DEBUGFS
	carl9170_debugfs_unregister(ar);
#endif /* CONFIG_CARL9170_DEBUGFS */

#ifdef CONFIG_CARL9170_WPC
	if (ar->wps.pbc) {
		input_unregister_device(ar->wps.pbc);
		ar->wps.pbc = NULL;
	}
#endif /* CONFIG_CARL9170_WPC */

#ifdef CONFIG_CARL9170_HWRNG
	carl9170_unregister_hwrng(ar);
#endif /* CONFIG_CARL9170_HWRNG */

	carl9170_cancel_worker(ar);
	cancel_work_sync(&ar->restart_work);

	ieee80211_unregister_hw(ar->hw);
}