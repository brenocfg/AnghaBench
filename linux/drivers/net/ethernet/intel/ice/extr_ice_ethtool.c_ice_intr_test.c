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
typedef  int u64 ;
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct ice_pf {scalar_t__ sw_int_count; int /*<<< orphan*/  oicr_idx; int /*<<< orphan*/  hw; } ;
struct ice_netdev_priv {TYPE_1__* vsi; } ;
struct TYPE_2__ {struct ice_pf* back; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLINT_DYN_CTL (int /*<<< orphan*/ ) ; 
 int GLINT_DYN_CTL_INTENA_MSK_M ; 
 int GLINT_DYN_CTL_SWINT_TRIG_M ; 
 int GLINT_DYN_CTL_SW_ITR_INDX_M ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u64 ice_intr_test(struct net_device *netdev)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_pf *pf = np->vsi->back;
	u16 swic_old = pf->sw_int_count;

	netdev_info(netdev, "interrupt test\n");

	wr32(&pf->hw, GLINT_DYN_CTL(pf->oicr_idx),
	     GLINT_DYN_CTL_SW_ITR_INDX_M |
	     GLINT_DYN_CTL_INTENA_MSK_M |
	     GLINT_DYN_CTL_SWINT_TRIG_M);

	usleep_range(1000, 2000);
	return (swic_old == pf->sw_int_count);
}