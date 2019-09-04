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
struct xgene_enet_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CONFIG_1_ADDR ; 
 int /*<<< orphan*/  xgene_enet_rd_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_enet_wr_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_sgmac_rxtx(struct xgene_enet_pdata *p, u32 bits, bool set)
{
	u32 data;

	data = xgene_enet_rd_mac(p, MAC_CONFIG_1_ADDR);

	if (set)
		data |= bits;
	else
		data &= ~bits;

	xgene_enet_wr_mac(p, MAC_CONFIG_1_ADDR, data);
}