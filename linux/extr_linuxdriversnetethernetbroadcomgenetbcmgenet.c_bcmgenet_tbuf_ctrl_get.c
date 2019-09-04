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
typedef  int /*<<< orphan*/  u32 ;
struct bcmgenet_priv {TYPE_1__* hw_params; scalar_t__ base; } ;
struct TYPE_2__ {scalar_t__ tbuf_offset; } ;

/* Variables and functions */
 scalar_t__ GENET_IS_V1 (struct bcmgenet_priv*) ; 
 scalar_t__ TBUF_CTRL ; 
 int /*<<< orphan*/  TBUF_CTRL_V1 ; 
 int /*<<< orphan*/  bcmgenet_rbuf_readl (struct bcmgenet_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_readl (scalar_t__) ; 

__attribute__((used)) static inline u32 bcmgenet_tbuf_ctrl_get(struct bcmgenet_priv *priv)
{
	if (GENET_IS_V1(priv))
		return bcmgenet_rbuf_readl(priv, TBUF_CTRL_V1);
	else
		return bcmgenet_readl(priv->base +
				      priv->hw_params->tbuf_offset + TBUF_CTRL);
}