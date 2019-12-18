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
struct net_device {int dummy; } ;
struct enetc_pf {int total_vfs; } ;
struct enetc_ndev_priv {TYPE_1__* si; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENETC_PSICFGR0 (int) ; 
 int ENETC_PSICFGR0_ASE ; 
 int enetc_port_rd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_port_wr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct enetc_pf* enetc_si_priv (TYPE_1__*) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int enetc_pf_set_vf_spoofchk(struct net_device *ndev, int vf, bool en)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);
	struct enetc_pf *pf = enetc_si_priv(priv->si);
	u32 cfgr;

	if (vf >= pf->total_vfs)
		return -EINVAL;

	cfgr = enetc_port_rd(&priv->si->hw, ENETC_PSICFGR0(vf + 1));
	cfgr = (cfgr & ~ENETC_PSICFGR0_ASE) | (en ? ENETC_PSICFGR0_ASE : 0);
	enetc_port_wr(&priv->si->hw, ENETC_PSICFGR0(vf + 1), cfgr);

	return 0;
}