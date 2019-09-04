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
 int /*<<< orphan*/  AXGMAC_CONFIG_0 ; 
 int /*<<< orphan*/  HSTMACRST ; 
 int /*<<< orphan*/  xgene_enet_wr_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_xgmac_reset(struct xgene_enet_pdata *pdata)
{
	xgene_enet_wr_mac(pdata, AXGMAC_CONFIG_0, HSTMACRST);
	xgene_enet_wr_mac(pdata, AXGMAC_CONFIG_0, 0);
}