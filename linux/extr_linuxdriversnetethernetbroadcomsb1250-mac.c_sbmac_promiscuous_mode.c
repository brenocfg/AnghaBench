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
typedef  int /*<<< orphan*/  uint64_t ;
struct sbmac_softc {scalar_t__ sbm_state; int /*<<< orphan*/  sbm_rxfilter; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MAC_ALLPKT_EN ; 
 int /*<<< orphan*/  __raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sbmac_state_on ; 

__attribute__((used)) static void sbmac_promiscuous_mode(struct sbmac_softc *sc,int onoff)
{
	uint64_t reg;

	if (sc->sbm_state != sbmac_state_on)
		return;

	if (onoff) {
		reg = __raw_readq(sc->sbm_rxfilter);
		reg |= M_MAC_ALLPKT_EN;
		__raw_writeq(reg, sc->sbm_rxfilter);
	}
	else {
		reg = __raw_readq(sc->sbm_rxfilter);
		reg &= ~M_MAC_ALLPKT_EN;
		__raw_writeq(reg, sc->sbm_rxfilter);
	}
}