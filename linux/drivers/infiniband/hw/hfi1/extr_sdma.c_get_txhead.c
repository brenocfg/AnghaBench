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
struct sdma_txreq {int dummy; } ;
struct sdma_engine {size_t tx_head; size_t sdma_mask; struct sdma_txreq** tx_ring; } ;

/* Variables and functions */

__attribute__((used)) static inline struct sdma_txreq *get_txhead(struct sdma_engine *sde)
{
	return sde->tx_ring[sde->tx_head & sde->sdma_mask];
}