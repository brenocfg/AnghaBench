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
struct sbmac_softc {int /*<<< orphan*/  sbm_rxdma; int /*<<< orphan*/  sbm_txdma; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbdma_uninitctx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sbmac_uninitctx(struct sbmac_softc *sc)
{
	sbdma_uninitctx(&(sc->sbm_txdma));
	sbdma_uninitctx(&(sc->sbm_rxdma));
}