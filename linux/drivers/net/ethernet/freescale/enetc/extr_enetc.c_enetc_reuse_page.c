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
struct enetc_rx_swbd {int dummy; } ;
struct enetc_bdr {size_t next_to_alloc; struct enetc_rx_swbd* rx_swbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  enetc_bdr_idx_inc (struct enetc_bdr*,size_t*) ; 

__attribute__((used)) static void enetc_reuse_page(struct enetc_bdr *rx_ring,
			     struct enetc_rx_swbd *old)
{
	struct enetc_rx_swbd *new;

	new = &rx_ring->rx_swbd[rx_ring->next_to_alloc];

	/* next buf that may reuse a page */
	enetc_bdr_idx_inc(rx_ring, &rx_ring->next_to_alloc);

	/* copy page reference */
	*new = *old;
}