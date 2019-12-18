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
struct bcmgenet_priv {TYPE_1__* hw_params; } ;
struct TYPE_2__ {int hfb_filter_cnt; int hfb_filter_size; } ;

/* Variables and functions */
 int DMA_INDEX2RING_0 ; 
 int DMA_INDEX2RING_7 ; 
 scalar_t__ HFB_CTRL ; 
 scalar_t__ HFB_FLT_ENABLE_V3PLUS ; 
 scalar_t__ HFB_FLT_LEN_V3PLUS ; 
 int /*<<< orphan*/  bcmgenet_hfb_reg_writel (struct bcmgenet_priv*,int,scalar_t__) ; 
 int /*<<< orphan*/  bcmgenet_hfb_writel (struct bcmgenet_priv*,int,int) ; 
 int /*<<< orphan*/  bcmgenet_rdma_writel (struct bcmgenet_priv*,int,int) ; 

__attribute__((used)) static void bcmgenet_hfb_clear(struct bcmgenet_priv *priv)
{
	u32 i;

	bcmgenet_hfb_reg_writel(priv, 0x0, HFB_CTRL);
	bcmgenet_hfb_reg_writel(priv, 0x0, HFB_FLT_ENABLE_V3PLUS);
	bcmgenet_hfb_reg_writel(priv, 0x0, HFB_FLT_ENABLE_V3PLUS + 4);

	for (i = DMA_INDEX2RING_0; i <= DMA_INDEX2RING_7; i++)
		bcmgenet_rdma_writel(priv, 0x0, i);

	for (i = 0; i < (priv->hw_params->hfb_filter_cnt / 4); i++)
		bcmgenet_hfb_reg_writel(priv, 0x0,
					HFB_FLT_LEN_V3PLUS + i * sizeof(u32));

	for (i = 0; i < priv->hw_params->hfb_filter_cnt *
			priv->hw_params->hfb_filter_size; i++)
		bcmgenet_hfb_writel(priv, 0x0, i * sizeof(u32));
}