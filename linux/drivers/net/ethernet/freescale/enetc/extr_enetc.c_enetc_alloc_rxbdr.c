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
typedef  union enetc_rx_bd {int dummy; } enetc_rx_bd ;
struct enetc_rx_swbd {int dummy; } ;
struct enetc_bdr {int bd_count; scalar_t__ next_to_alloc; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/  rx_swbd; } ;

/* Variables and functions */
 int ENOMEM ; 
 int enetc_dma_alloc_bdr (struct enetc_bdr*,int) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vzalloc (int) ; 

__attribute__((used)) static int enetc_alloc_rxbdr(struct enetc_bdr *rxr)
{
	int err;

	rxr->rx_swbd = vzalloc(rxr->bd_count * sizeof(struct enetc_rx_swbd));
	if (!rxr->rx_swbd)
		return -ENOMEM;

	err = enetc_dma_alloc_bdr(rxr, sizeof(union enetc_rx_bd));
	if (err) {
		vfree(rxr->rx_swbd);
		return err;
	}

	rxr->next_to_clean = 0;
	rxr->next_to_use = 0;
	rxr->next_to_alloc = 0;

	return 0;
}