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
struct TYPE_2__ {unsigned int in_buf_size; } ;
struct qeth_card {TYPE_1__ qdio; struct net_device* dev; } ;
struct net_device {unsigned int mtu; unsigned int max_mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETH_DATA_LEN ; 
 unsigned int ETH_MAX_MTU ; 
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 scalar_t__ IS_LAYER2 (struct qeth_card*) ; 
 int PAGE_SIZE ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  qeth_free_qdio_queues (struct qeth_card*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int qeth_update_max_mtu(struct qeth_card *card, unsigned int max_mtu)
{
	struct net_device *dev = card->dev;
	unsigned int new_mtu;

	if (!max_mtu) {
		/* IQD needs accurate max MTU to set up its RX buffers: */
		if (IS_IQD(card))
			return -EINVAL;
		/* tolerate quirky HW: */
		max_mtu = ETH_MAX_MTU;
	}

	rtnl_lock();
	if (IS_IQD(card)) {
		/* move any device with default MTU to new max MTU: */
		new_mtu = (dev->mtu == dev->max_mtu) ? max_mtu : dev->mtu;

		/* adjust RX buffer size to new max MTU: */
		card->qdio.in_buf_size = max_mtu + 2 * PAGE_SIZE;
		if (dev->max_mtu && dev->max_mtu != max_mtu)
			qeth_free_qdio_queues(card);
	} else {
		if (dev->mtu)
			new_mtu = dev->mtu;
		/* default MTUs for first setup: */
		else if (IS_LAYER2(card))
			new_mtu = ETH_DATA_LEN;
		else
			new_mtu = ETH_DATA_LEN - 8; /* allow for LLC + SNAP */
	}

	dev->max_mtu = max_mtu;
	dev->mtu = min(new_mtu, max_mtu);
	rtnl_unlock();
	return 0;
}