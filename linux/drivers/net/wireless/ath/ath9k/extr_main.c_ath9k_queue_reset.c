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
struct ath_softc {int /*<<< orphan*/  hw_reset_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int /*<<< orphan*/  op_flags; } ;
typedef  enum ath_reset_type { ____Placeholder_ath_reset_type } ath_reset_type ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_OP_HW_RESET ; 
 int /*<<< orphan*/  RESET_STAT_INC (struct ath_softc*,int) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_kill_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath9k_queue_reset(struct ath_softc *sc, enum ath_reset_type type)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
#ifdef CONFIG_ATH9K_DEBUGFS
	RESET_STAT_INC(sc, type);
#endif
	ath9k_hw_kill_interrupts(sc->sc_ah);
	set_bit(ATH_OP_HW_RESET, &common->op_flags);
	ieee80211_queue_work(sc->hw, &sc->hw_reset_work);
}