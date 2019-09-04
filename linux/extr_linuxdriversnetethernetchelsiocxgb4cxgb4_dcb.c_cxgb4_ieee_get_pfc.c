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
struct port_dcb_info {int msgs; int /*<<< orphan*/  pfcen; int /*<<< orphan*/  pfc_num_tcs_supported; } ;
struct port_info {struct port_dcb_info dcb; } ;
struct net_device {int dummy; } ;
struct ieee_pfc {int /*<<< orphan*/  pfc_en; int /*<<< orphan*/  pfc_cap; } ;

/* Variables and functions */
 int CXGB4_DCB_FW_PFC ; 
 int /*<<< orphan*/  bitswap_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee_pfc*,int /*<<< orphan*/ ,int) ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 

__attribute__((used)) static int cxgb4_ieee_get_pfc(struct net_device *dev, struct ieee_pfc *pfc)
{
	struct port_info *pi = netdev2pinfo(dev);
	struct port_dcb_info *dcb = &pi->dcb;

	memset(pfc, 0, sizeof(struct ieee_pfc));

	if (!(dcb->msgs & CXGB4_DCB_FW_PFC))
		return 0;

	pfc->pfc_cap = dcb->pfc_num_tcs_supported;
	pfc->pfc_en = bitswap_1(dcb->pfcen);

	return 0;
}