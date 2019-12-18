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
typedef  int u32 ;
struct pdc_state {int nrxpost; int ntxpost; int /*<<< orphan*/  tx_ring_full; int /*<<< orphan*/  txout; int /*<<< orphan*/  txin; int /*<<< orphan*/  rx_ring_full; int /*<<< orphan*/  rxout; int /*<<< orphan*/  rxin; } ;

/* Variables and functions */
 int NRXDACTIVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int NTXDACTIVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool pdc_rings_full(struct pdc_state *pdcs, int tx_cnt, int rx_cnt)
{
	u32 rx_avail;
	u32 tx_avail;
	bool full = false;

	/* Check if the tx and rx rings are likely to have enough space */
	rx_avail = pdcs->nrxpost - NRXDACTIVE(pdcs->rxin, pdcs->rxout,
					      pdcs->nrxpost);
	if (unlikely(rx_cnt > rx_avail)) {
		pdcs->rx_ring_full++;
		full = true;
	}

	if (likely(!full)) {
		tx_avail = pdcs->ntxpost - NTXDACTIVE(pdcs->txin, pdcs->txout,
						      pdcs->ntxpost);
		if (unlikely(tx_cnt > tx_avail)) {
			pdcs->tx_ring_full++;
			full = true;
		}
	}
	return full;
}