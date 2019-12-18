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
struct TYPE_2__ {int /*<<< orphan*/  dvlan; } ;
struct stmmac_priv {TYPE_1__ dma_cap; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stmmac_test_vlanoff_common (struct stmmac_priv*,int) ; 

__attribute__((used)) static int stmmac_test_svlanoff(struct stmmac_priv *priv)
{
	if (!priv->dma_cap.dvlan)
		return -EOPNOTSUPP;
	return stmmac_test_vlanoff_common(priv, true);
}