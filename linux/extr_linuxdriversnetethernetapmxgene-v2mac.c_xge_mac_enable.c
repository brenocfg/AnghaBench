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
struct xge_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CONFIG_1 ; 
 int RX_EN ; 
 int TX_EN ; 
 int xge_rd_csr (struct xge_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xge_wr_csr (struct xge_pdata*,int /*<<< orphan*/ ,int) ; 

void xge_mac_enable(struct xge_pdata *pdata)
{
	u32 data;

	data = xge_rd_csr(pdata, MAC_CONFIG_1);
	data |= TX_EN | RX_EN;
	xge_wr_csr(pdata, MAC_CONFIG_1, data);

	data = xge_rd_csr(pdata, MAC_CONFIG_1);
}