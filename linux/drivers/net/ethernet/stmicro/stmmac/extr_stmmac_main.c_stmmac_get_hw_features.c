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
struct stmmac_priv {int /*<<< orphan*/  dma_cap; int /*<<< orphan*/  ioaddr; } ;

/* Variables and functions */
 scalar_t__ stmmac_get_hw_feature (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int stmmac_get_hw_features(struct stmmac_priv *priv)
{
	return stmmac_get_hw_feature(priv, priv->ioaddr, &priv->dma_cap) == 0;
}