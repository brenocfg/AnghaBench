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
struct TYPE_2__ {int /*<<< orphan*/  pfc_num_tcs_supported; int /*<<< orphan*/  pfcen; } ;
struct port_info {TYPE_1__ dcb; } ;
struct net_device {int dummy; } ;
struct cee_pfc {int /*<<< orphan*/  tcs_supported; int /*<<< orphan*/  pfc_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_NUMTCS_ATTR_PFC ; 
 int /*<<< orphan*/  bitswap_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_getnumtcs (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct port_info* netdev2pinfo (struct net_device*) ; 

__attribute__((used)) static int cxgb4_cee_peer_getpfc(struct net_device *dev, struct cee_pfc *pfc)
{
	struct port_info *pi = netdev2pinfo(dev);

	cxgb4_getnumtcs(dev, DCB_NUMTCS_ATTR_PFC, &(pfc->tcs_supported));

	/* Firmware sends this to us in a formwat that is a bit flipped version
	 * of spec, correct it before we send it to host. This is taken care of
	 * by bit shifting in other uses of pfcen
	 */
	pfc->pfc_en = bitswap_1(pi->dcb.pfcen);

	pfc->tcs_supported = pi->dcb.pfc_num_tcs_supported;

	return 0;
}