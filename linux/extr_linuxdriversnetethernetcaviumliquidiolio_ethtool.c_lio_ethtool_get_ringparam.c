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
typedef  void* u32 ;
struct octeon_device {TYPE_2__** instr_queue; TYPE_1__** droq; } ;
struct octeon_config {int dummy; } ;
struct net_device {int dummy; } ;
struct lio {int /*<<< orphan*/  ifidx; struct octeon_device* oct_dev; } ;
struct ethtool_ringparam {scalar_t__ rx_jumbo_max_pending; scalar_t__ rx_mini_max_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; void* rx_max_pending; void* rx_pending; void* tx_max_pending; void* tx_pending; } ;
struct TYPE_4__ {void* max_count; } ;
struct TYPE_3__ {void* max_count; } ;

/* Variables and functions */
 void* CFG_GET_NUM_RX_DESCS_NIC_IF (struct octeon_config*,int /*<<< orphan*/ ) ; 
 void* CFG_GET_NUM_TX_DESCS_NIC_IF (struct octeon_config*,int /*<<< orphan*/ ) ; 
 struct octeon_config* CHIP_CONF (struct octeon_device*,int /*<<< orphan*/ ) ; 
 void* CN23XX_MAX_IQ_DESCRIPTORS ; 
 void* CN23XX_MAX_OQ_DESCRIPTORS ; 
 void* CN6XXX_MAX_IQ_DESCRIPTORS ; 
 void* CN6XXX_MAX_OQ_DESCRIPTORS ; 
 struct lio* GET_LIO (struct net_device*) ; 
 int /*<<< orphan*/  LIO_IFSTATE_RESETTING ; 
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN23XX_VF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN6XXX (struct octeon_device*) ; 
 int /*<<< orphan*/  cn6xxx ; 
 scalar_t__ ifstate_check (struct lio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lio_ethtool_get_ringparam(struct net_device *netdev,
			  struct ethtool_ringparam *ering)
{
	struct lio *lio = GET_LIO(netdev);
	struct octeon_device *oct = lio->oct_dev;
	u32 tx_max_pending = 0, rx_max_pending = 0, tx_pending = 0,
	    rx_pending = 0;

	if (ifstate_check(lio, LIO_IFSTATE_RESETTING))
		return;

	if (OCTEON_CN6XXX(oct)) {
		struct octeon_config *conf6x = CHIP_CONF(oct, cn6xxx);

		tx_max_pending = CN6XXX_MAX_IQ_DESCRIPTORS;
		rx_max_pending = CN6XXX_MAX_OQ_DESCRIPTORS;
		rx_pending = CFG_GET_NUM_RX_DESCS_NIC_IF(conf6x, lio->ifidx);
		tx_pending = CFG_GET_NUM_TX_DESCS_NIC_IF(conf6x, lio->ifidx);
	} else if (OCTEON_CN23XX_PF(oct) || OCTEON_CN23XX_VF(oct)) {
		tx_max_pending = CN23XX_MAX_IQ_DESCRIPTORS;
		rx_max_pending = CN23XX_MAX_OQ_DESCRIPTORS;
		rx_pending = oct->droq[0]->max_count;
		tx_pending = oct->instr_queue[0]->max_count;
	}

	ering->tx_pending = tx_pending;
	ering->tx_max_pending = tx_max_pending;
	ering->rx_pending = rx_pending;
	ering->rx_max_pending = rx_max_pending;
	ering->rx_mini_pending = 0;
	ering->rx_jumbo_pending = 0;
	ering->rx_mini_max_pending = 0;
	ering->rx_jumbo_max_pending = 0;
}