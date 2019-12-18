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
typedef  int /*<<< orphan*/  u32 ;
struct ftgmac100 {int tx_q_entries; int /*<<< orphan*/  txdes0_edotr_mask; } ;

/* Variables and functions */

__attribute__((used)) static u32 ftgmac100_base_tx_ctlstat(struct ftgmac100 *priv,
				     unsigned int index)
{
	if (index == (priv->tx_q_entries - 1))
		return priv->txdes0_edotr_mask;
	else
		return 0;
}