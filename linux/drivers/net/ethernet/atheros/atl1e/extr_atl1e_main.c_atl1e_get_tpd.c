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
typedef  size_t u16 ;
struct atl1e_tx_ring {size_t next_to_use; scalar_t__ count; struct atl1e_tpd_desc* desc; } ;
struct atl1e_tpd_desc {int dummy; } ;
struct atl1e_adapter {struct atl1e_tx_ring tx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct atl1e_tpd_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct atl1e_tpd_desc *atl1e_get_tpd(struct atl1e_adapter *adapter)
{
	struct atl1e_tx_ring *tx_ring = &adapter->tx_ring;
	u16 next_to_use = 0;

	next_to_use = tx_ring->next_to_use;
	if (++tx_ring->next_to_use == tx_ring->count)
		tx_ring->next_to_use = 0;

	memset(&tx_ring->desc[next_to_use], 0, sizeof(struct atl1e_tpd_desc));
	return &tx_ring->desc[next_to_use];
}