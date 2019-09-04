#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_8__ {scalar_t__ sriov_enabled; } ;
struct TYPE_6__ {int /*<<< orphan*/  liquidio_firmware_version; } ;
struct octeon_device {int num_iqs; TYPE_3__ sriov_info; TYPE_2__* pci_dev; TYPE_1__ fw_info; } ;
struct octeon_config {int dummy; } ;
struct net_device {TYPE_5__* netdev_ops; } ;
struct TYPE_9__ {int num_txpciq; } ;
struct lio {TYPE_4__ linfo; struct octeon_device* oct_dev; } ;
struct ethtool_channels {int combined_count; scalar_t__ tx_count; scalar_t__ rx_count; scalar_t__ other_count; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* ndo_open ) (struct net_device*) ;int /*<<< orphan*/  (* ndo_stop ) (struct net_device*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CFG_GET_IQ_MAX_Q (struct octeon_config*) ; 
 struct octeon_config* CHIP_CONF (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int CN23XX_PKT_INPUT_CTL_RPVF_MASK ; 
 int CN23XX_PKT_INPUT_CTL_RPVF_POS ; 
 int CN23XX_VF_SLI_IQ_PKT_CONTROL64 (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  LIO_IFSTATE_RESETTING ; 
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN23XX_VF (struct octeon_device*) ; 
 int /*<<< orphan*/  cn23xx_pf ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ifstate_reset (struct lio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifstate_set (struct lio*,int /*<<< orphan*/ ) ; 
 scalar_t__ lio_reset_queues (struct net_device*,int) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int octeon_read_csr64 (struct octeon_device*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*) ; 

__attribute__((used)) static int
lio_ethtool_set_channels(struct net_device *dev,
			 struct ethtool_channels *channel)
{
	u32 combined_count, max_combined;
	struct lio *lio = GET_LIO(dev);
	struct octeon_device *oct = lio->oct_dev;
	int stopped = 0;

	if (strcmp(oct->fw_info.liquidio_firmware_version, "1.6.1") < 0) {
		dev_err(&oct->pci_dev->dev, "Minimum firmware version required is 1.6.1\n");
		return -EINVAL;
	}

	if (!channel->combined_count || channel->other_count ||
	    channel->rx_count || channel->tx_count)
		return -EINVAL;

	combined_count = channel->combined_count;

	if (OCTEON_CN23XX_PF(oct)) {
		if (oct->sriov_info.sriov_enabled) {
			max_combined = lio->linfo.num_txpciq;
		} else {
			struct octeon_config *conf23_pf =
				CHIP_CONF(oct,
					  cn23xx_pf);

			max_combined =
				CFG_GET_IQ_MAX_Q(conf23_pf);
		}
	} else if (OCTEON_CN23XX_VF(oct)) {
		u64 reg_val = 0ULL;
		u64 ctrl = CN23XX_VF_SLI_IQ_PKT_CONTROL64(0);

		reg_val = octeon_read_csr64(oct, ctrl);
		reg_val = reg_val >> CN23XX_PKT_INPUT_CTL_RPVF_POS;
		max_combined = reg_val & CN23XX_PKT_INPUT_CTL_RPVF_MASK;
	} else {
		return -EINVAL;
	}

	if (combined_count > max_combined || combined_count < 1)
		return -EINVAL;

	if (combined_count == oct->num_iqs)
		return 0;

	ifstate_set(lio, LIO_IFSTATE_RESETTING);

	if (netif_running(dev)) {
		dev->netdev_ops->ndo_stop(dev);
		stopped = 1;
	}

	if (lio_reset_queues(dev, combined_count))
		return -EINVAL;

	if (stopped)
		dev->netdev_ops->ndo_open(dev);

	ifstate_reset(lio, LIO_IFSTATE_RESETTING);

	return 0;
}