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
struct ath_softc {int /*<<< orphan*/  mci_work; int /*<<< orphan*/  sc_ah; int /*<<< orphan*/  hw_pll_work; int /*<<< orphan*/  hw_check_work; int /*<<< orphan*/  paprd_work; } ;

/* Variables and functions */
 scalar_t__ ath9k_hw_mci_is_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ath_cancel_work(struct ath_softc *sc)
{
	cancel_work_sync(&sc->paprd_work);
	cancel_delayed_work_sync(&sc->hw_check_work);
	cancel_delayed_work_sync(&sc->hw_pll_work);

#ifdef CONFIG_ATH9K_BTCOEX_SUPPORT
	if (ath9k_hw_mci_is_enabled(sc->sc_ah))
		cancel_work_sync(&sc->mci_work);
#endif
}