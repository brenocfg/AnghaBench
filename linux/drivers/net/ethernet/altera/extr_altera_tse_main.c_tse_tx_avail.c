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
typedef  scalar_t__ u32 ;
struct altera_tse_private {scalar_t__ tx_prod; scalar_t__ tx_ring_size; scalar_t__ tx_cons; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 tse_tx_avail(struct altera_tse_private *priv)
{
	return priv->tx_cons + priv->tx_ring_size - priv->tx_prod - 1;
}