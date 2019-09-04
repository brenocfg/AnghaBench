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
struct ftgmac100_rxdes {int dummy; } ;
struct ftgmac100 {int rx_q_entries; struct ftgmac100_rxdes* rxdes; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ftgmac100_alloc_rx_buf (struct ftgmac100*,int,struct ftgmac100_rxdes*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftgmac100_alloc_rx_buffers(struct ftgmac100 *priv)
{
	int i;

	for (i = 0; i < priv->rx_q_entries; i++) {
		struct ftgmac100_rxdes *rxdes = &priv->rxdes[i];

		if (ftgmac100_alloc_rx_buf(priv, i, rxdes, GFP_KERNEL))
			return -ENOMEM;
	}
	return 0;
}