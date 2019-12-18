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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct m_can_classdev {int version; int /*<<< orphan*/ * tx_skb; int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_CAN_TXFQS ; 
 int TXFQS_TFQPI_MASK ; 
 int TXFQS_TFQPI_SHIFT ; 
 int /*<<< orphan*/  can_free_echo_skb (int /*<<< orphan*/ ,int) ; 
 int m_can_read (struct m_can_classdev*,int /*<<< orphan*/ ) ; 
 struct m_can_classdev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void m_can_clean(struct net_device *net)
{
	struct m_can_classdev *cdev = netdev_priv(net);

	if (cdev->tx_skb) {
		int putidx = 0;

		net->stats.tx_errors++;
		if (cdev->version > 30)
			putidx = ((m_can_read(cdev, M_CAN_TXFQS) &
				   TXFQS_TFQPI_MASK) >> TXFQS_TFQPI_SHIFT);

		can_free_echo_skb(cdev->net, putidx);
		cdev->tx_skb = NULL;
	}
}