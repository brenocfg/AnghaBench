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
 int /*<<< orphan*/  XG_LINK_STATUS_ADDR ; 
 int /*<<< orphan*/  xgene_enet_rd_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 xgene_enet_link_status(struct xgene_enet_pdata *pdata)
{
	u32 data;

	xgene_enet_rd_csr(pdata, XG_LINK_STATUS_ADDR, &data);

	return data;
}