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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct kvaser_pciefd_can {int /*<<< orphan*/  bec_poll_timer; scalar_t__ reg_base; TYPE_1__ can; int /*<<< orphan*/  flush_comp; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ KVASER_PCIEFD_KCAN_IEN_REG ; 
 int /*<<< orphan*/  KVASER_PCIEFD_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  completion_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kvaser_pciefd_start_controller_flush (struct kvaser_pciefd_can*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct kvaser_pciefd_can* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvaser_pciefd_stop(struct net_device *netdev)
{
	struct kvaser_pciefd_can *can = netdev_priv(netdev);
	int ret = 0;

	/* Don't interrupt ongoing flush */
	if (!completion_done(&can->flush_comp))
		kvaser_pciefd_start_controller_flush(can);

	if (!wait_for_completion_timeout(&can->flush_comp,
					 KVASER_PCIEFD_WAIT_TIMEOUT)) {
		netdev_err(can->can.dev, "Timeout during stop\n");
		ret = -ETIMEDOUT;
	} else {
		iowrite32(0, can->reg_base + KVASER_PCIEFD_KCAN_IEN_REG);
		del_timer(&can->bec_poll_timer);
	}
	close_candev(netdev);

	return ret;
}