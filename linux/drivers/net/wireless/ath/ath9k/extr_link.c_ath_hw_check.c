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
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int dummy; } ;
typedef  enum ath_reset_type { ____Placeholder_ath_reset_type } ath_reset_type ;

/* Variables and functions */
 int /*<<< orphan*/  RESET ; 
 int RESET_TYPE_MAC_HANG ; 
 int ath9k_hw_check_alive (int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_ps_restore (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_ps_wakeup (struct ath_softc*) ; 
 int /*<<< orphan*/  ath9k_queue_reset (struct ath_softc*,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

bool ath_hw_check(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	enum ath_reset_type type;
	bool is_alive;

	ath9k_ps_wakeup(sc);

	is_alive = ath9k_hw_check_alive(sc->sc_ah);

	if (!is_alive) {
		ath_dbg(common, RESET,
			"HW hang detected, schedule chip reset\n");
		type = RESET_TYPE_MAC_HANG;
		ath9k_queue_reset(sc, type);
	}

	ath9k_ps_restore(sc);

	return is_alive;
}