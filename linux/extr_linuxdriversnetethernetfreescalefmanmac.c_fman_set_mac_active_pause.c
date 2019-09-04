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
typedef  int /*<<< orphan*/  u16 ;
struct mac_device {int rx_pause_active; int (* set_rx_pause ) (struct fman_mac*,int) ;int tx_pause_active; int (* set_tx_pause ) (struct fman_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct fman_mac* fman_mac; } ;
struct fman_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSL_FM_PAUSE_TIME_DISABLE ; 
 int /*<<< orphan*/  FSL_FM_PAUSE_TIME_ENABLE ; 
 scalar_t__ likely (int) ; 
 int stub1 (struct fman_mac*,int) ; 
 int stub2 (struct fman_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fman_set_mac_active_pause(struct mac_device *mac_dev, bool rx, bool tx)
{
	struct fman_mac *fman_mac = mac_dev->fman_mac;
	int err = 0;

	if (rx != mac_dev->rx_pause_active) {
		err = mac_dev->set_rx_pause(fman_mac, rx);
		if (likely(err == 0))
			mac_dev->rx_pause_active = rx;
	}

	if (tx != mac_dev->tx_pause_active) {
		u16 pause_time = (tx ? FSL_FM_PAUSE_TIME_ENABLE :
					 FSL_FM_PAUSE_TIME_DISABLE);

		err = mac_dev->set_tx_pause(fman_mac, 0, pause_time, 0);

		if (likely(err == 0))
			mac_dev->tx_pause_active = tx;
	}

	return err;
}