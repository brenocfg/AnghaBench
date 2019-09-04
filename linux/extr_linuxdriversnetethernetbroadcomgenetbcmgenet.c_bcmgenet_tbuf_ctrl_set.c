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
 int /*<<< orphan*/  bcmgenet_rbuf_writel (struct bcmgenet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcmgenet_writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void bcmgenet_tbuf_ctrl_set(struct bcmgenet_priv *priv, u32 val)
{
	if (GENET_IS_V1(priv))
		bcmgenet_rbuf_writel(priv, val, TBUF_CTRL_V1);
	else
		bcmgenet_writel(val, priv->base +
				priv->hw_params->tbuf_offset + TBUF_CTRL);
}