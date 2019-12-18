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
struct macsec_tx_sc {int /*<<< orphan*/  scb; int /*<<< orphan*/  end_station; scalar_t__ send_sci; } ;
struct macsec_secy {int n_rx_sc; struct macsec_tx_sc tx_sc; } ;

/* Variables and functions */

__attribute__((used)) static bool send_sci(const struct macsec_secy *secy)
{
	const struct macsec_tx_sc *tx_sc = &secy->tx_sc;

	return tx_sc->send_sci ||
		(secy->n_rx_sc > 1 && !tx_sc->end_station && !tx_sc->scb);
}