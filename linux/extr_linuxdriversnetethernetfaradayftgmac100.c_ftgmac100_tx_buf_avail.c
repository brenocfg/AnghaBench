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
struct ftgmac100 {int tx_clean_pointer; int tx_pointer; int tx_q_entries; } ;

/* Variables and functions */

__attribute__((used)) static u32 ftgmac100_tx_buf_avail(struct ftgmac100 *priv)
{
	/* Returns the number of available slots in the TX queue
	 *
	 * This always leaves one free slot so we don't have to
	 * worry about empty vs. full, and this simplifies the
	 * test for ftgmac100_tx_buf_cleanable() below
	 */
	return (priv->tx_clean_pointer - priv->tx_pointer - 1) &
		(priv->tx_q_entries - 1);
}