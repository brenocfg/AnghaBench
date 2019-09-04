#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct octeon_device {TYPE_2__* pci_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct lio_vf_rep_req {TYPE_1__ rep_state; int /*<<< orphan*/  ifidx; int /*<<< orphan*/  req_type; } ;
struct lio_vf_rep_desc {int /*<<< orphan*/  ifstate; int /*<<< orphan*/  ifidx; struct octeon_device* oct; } ;
typedef  int /*<<< orphan*/  rep_cfg ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int LIO_IFSTATE_RUNNING ; 
 int /*<<< orphan*/  LIO_VF_REP_REQ_STATE ; 
 int /*<<< orphan*/  LIO_VF_REP_STATE_DOWN ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int lio_vf_rep_send_soft_command (struct octeon_device*,struct lio_vf_rep_req*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct lio_vf_rep_req*,int /*<<< orphan*/ ,int) ; 
 struct lio_vf_rep_desc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 

__attribute__((used)) static int
lio_vf_rep_stop(struct net_device *ndev)
{
	struct lio_vf_rep_desc *vf_rep = netdev_priv(ndev);
	struct lio_vf_rep_req rep_cfg;
	struct octeon_device *oct;
	int ret;

	oct = vf_rep->oct;

	memset(&rep_cfg, 0, sizeof(rep_cfg));
	rep_cfg.req_type = LIO_VF_REP_REQ_STATE;
	rep_cfg.ifidx = vf_rep->ifidx;
	rep_cfg.rep_state.state = LIO_VF_REP_STATE_DOWN;

	ret = lio_vf_rep_send_soft_command(oct, &rep_cfg,
					   sizeof(rep_cfg), NULL, 0);

	if (ret) {
		dev_err(&oct->pci_dev->dev,
			"VF_REP dev stop failed with err %d\n", ret);
		return -EIO;
	}

	atomic_set(&vf_rep->ifstate, (atomic_read(&vf_rep->ifstate) &
				      ~LIO_IFSTATE_RUNNING));

	netif_tx_disable(ndev);
	netif_carrier_off(ndev);

	return 0;
}