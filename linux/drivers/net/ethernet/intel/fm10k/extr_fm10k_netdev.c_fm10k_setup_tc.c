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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct fm10k_intfc {int /*<<< orphan*/  flags; TYPE_2__ hw; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FM10K_FLAG_SWPRI_CONFIG ; 
 int /*<<< orphan*/  fm10k_clear_queueing_scheme (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_close (struct net_device*) ; 
 int fm10k_init_queueing_scheme (struct fm10k_intfc*) ; 
 scalar_t__ fm10k_mac_pf ; 
 int /*<<< orphan*/  fm10k_mbx_free_irq (struct fm10k_intfc*) ; 
 int fm10k_mbx_request_irq (struct fm10k_intfc*) ; 
 int fm10k_open (struct net_device*) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_reset_tc (struct net_device*) ; 
 int /*<<< orphan*/  netdev_set_num_tc (struct net_device*,int) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fm10k_setup_tc(struct net_device *dev, u8 tc)
{
	struct fm10k_intfc *interface = netdev_priv(dev);
	int err;

	/* Currently only the PF supports priority classes */
	if (tc && (interface->hw.mac.type != fm10k_mac_pf))
		return -EINVAL;

	/* Hardware supports up to 8 traffic classes */
	if (tc > 8)
		return -EINVAL;

	/* Hardware has to reinitialize queues to match packet
	 * buffer alignment. Unfortunately, the hardware is not
	 * flexible enough to do this dynamically.
	 */
	if (netif_running(dev))
		fm10k_close(dev);

	fm10k_mbx_free_irq(interface);

	fm10k_clear_queueing_scheme(interface);

	/* we expect the prio_tc map to be repopulated later */
	netdev_reset_tc(dev);
	netdev_set_num_tc(dev, tc);

	err = fm10k_init_queueing_scheme(interface);
	if (err)
		goto err_queueing_scheme;

	err = fm10k_mbx_request_irq(interface);
	if (err)
		goto err_mbx_irq;

	err = netif_running(dev) ? fm10k_open(dev) : 0;
	if (err)
		goto err_open;

	/* flag to indicate SWPRI has yet to be updated */
	set_bit(FM10K_FLAG_SWPRI_CONFIG, interface->flags);

	return 0;
err_open:
	fm10k_mbx_free_irq(interface);
err_mbx_irq:
	fm10k_clear_queueing_scheme(interface);
err_queueing_scheme:
	netif_device_detach(dev);

	return err;
}