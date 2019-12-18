#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stmmac_priv {TYPE_1__* plat; } ;
struct TYPE_2__ {int tx_queues_to_use; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int __stmmac_test_jumbo (struct stmmac_priv*,int) ; 

__attribute__((used)) static int stmmac_test_mjumbo(struct stmmac_priv *priv)
{
	u32 chan, tx_cnt = priv->plat->tx_queues_to_use;
	int ret;

	if (tx_cnt <= 1)
		return -EOPNOTSUPP;

	for (chan = 0; chan < tx_cnt; chan++) {
		ret = __stmmac_test_jumbo(priv, chan);
		if (ret)
			return ret;
	}

	return 0;
}