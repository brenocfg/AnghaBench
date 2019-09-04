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
struct mtk_eth {int dummy; } ;
typedef  int __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_LRO_CTRL_DW2_CFG (int) ; 
 int /*<<< orphan*/  MTK_LRO_DIP_DW0_CFG (int) ; 
 int MTK_RING_MYIP_VLD ; 
 int mtk_r32 (struct mtk_eth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hwlro_val_ipaddr(struct mtk_eth *eth, int idx, __be32 ip)
{
	u32 reg_val;

	reg_val = mtk_r32(eth, MTK_LRO_CTRL_DW2_CFG(idx));

	/* invalidate the IP setting */
	mtk_w32(eth, (reg_val & ~MTK_RING_MYIP_VLD), MTK_LRO_CTRL_DW2_CFG(idx));

	mtk_w32(eth, ip, MTK_LRO_DIP_DW0_CFG(idx));

	/* validate the IP setting */
	mtk_w32(eth, (reg_val | MTK_RING_MYIP_VLD), MTK_LRO_CTRL_DW2_CFG(idx));
}