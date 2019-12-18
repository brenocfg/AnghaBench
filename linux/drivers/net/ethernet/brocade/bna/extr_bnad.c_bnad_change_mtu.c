#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct net_device {int mtu; } ;
struct bnad {int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int BNAD_FRAME_SIZE (int) ; 
 scalar_t__ BNAD_PCI_DEV_IS_CAT2 (struct bnad*) ; 
 int EBUSY ; 
 int bnad_mtu_set (struct bnad*,int) ; 
 int bnad_reinit_rx (struct bnad*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnad_change_mtu(struct net_device *netdev, int new_mtu)
{
	int err, mtu;
	struct bnad *bnad = netdev_priv(netdev);
	u32 rx_count = 0, frame, new_frame;

	mutex_lock(&bnad->conf_mutex);

	mtu = netdev->mtu;
	netdev->mtu = new_mtu;

	frame = BNAD_FRAME_SIZE(mtu);
	new_frame = BNAD_FRAME_SIZE(new_mtu);

	/* check if multi-buffer needs to be enabled */
	if (BNAD_PCI_DEV_IS_CAT2(bnad) &&
	    netif_running(bnad->netdev)) {
		/* only when transition is over 4K */
		if ((frame <= 4096 && new_frame > 4096) ||
		    (frame > 4096 && new_frame <= 4096))
			rx_count = bnad_reinit_rx(bnad);
	}

	/* rx_count > 0 - new rx created
	 *	- Linux set err = 0 and return
	 */
	err = bnad_mtu_set(bnad, new_frame);
	if (err)
		err = -EBUSY;

	mutex_unlock(&bnad->conf_mutex);
	return err;
}