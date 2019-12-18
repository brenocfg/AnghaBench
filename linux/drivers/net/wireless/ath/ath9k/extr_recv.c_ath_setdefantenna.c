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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ rxotherant; int /*<<< orphan*/  defant; } ;
struct ath_softc {TYPE_1__ rx; int /*<<< orphan*/  sc_ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_hw_setantenna (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath_setdefantenna(struct ath_softc *sc, u32 antenna)
{
	/* XXX block beacon interrupts */
	ath9k_hw_setantenna(sc->sc_ah, antenna);
	sc->rx.defant = antenna;
	sc->rx.rxotherant = 0;
}