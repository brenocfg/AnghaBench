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
struct xgene_enet_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CONFIG_1_ADDR ; 
 int /*<<< orphan*/  SOFT_RESET1 ; 
 int /*<<< orphan*/  xgene_enet_wr_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_sgmac_reset(struct xgene_enet_pdata *p)
{
	xgene_enet_wr_mac(p, MAC_CONFIG_1_ADDR, SOFT_RESET1);
	xgene_enet_wr_mac(p, MAC_CONFIG_1_ADDR, 0);
}