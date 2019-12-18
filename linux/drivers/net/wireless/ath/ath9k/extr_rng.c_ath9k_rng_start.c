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
struct ath_softc {int /*<<< orphan*/ * rng_task; struct ath_hw* sc_ah; } ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_rng_kthread ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,struct ath_softc*,char*) ; 

void ath9k_rng_start(struct ath_softc *sc)
{
	struct ath_hw *ah = sc->sc_ah;

	if (sc->rng_task)
		return;

	if (!AR_SREV_9300_20_OR_LATER(ah))
		return;

	sc->rng_task = kthread_run(ath9k_rng_kthread, sc, "ath9k-hwrng");
	if (IS_ERR(sc->rng_task))
		sc->rng_task = NULL;
}