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
struct wilc_vif {int /*<<< orphan*/  periodic_rssi; struct host_if_drv* hif_drv; struct wilc* wilc; } ;
struct wilc {scalar_t__ clients_count; int /*<<< orphan*/  deinit_lock; } ;
struct net_device {int dummy; } ;
struct host_if_drv {scalar_t__ p2p_timeout; int /*<<< orphan*/  hif_state; int /*<<< orphan*/  remain_on_ch_timer; int /*<<< orphan*/  connect_timer; int /*<<< orphan*/  scan_timer; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HOST_IF_IDLE ; 
 int /*<<< orphan*/  get_periodic_rssi ; 
 scalar_t__ jiffies ; 
 struct host_if_drv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listen_timer_cb ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  timer_connect_cb ; 
 int /*<<< orphan*/  timer_scan_cb ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wilc_init(struct net_device *dev, struct host_if_drv **hif_drv_handler)
{
	struct host_if_drv *hif_drv;
	struct wilc_vif *vif = netdev_priv(dev);
	struct wilc *wilc = vif->wilc;

	hif_drv  = kzalloc(sizeof(*hif_drv), GFP_KERNEL);
	if (!hif_drv)
		return -ENOMEM;

	*hif_drv_handler = hif_drv;

	vif->hif_drv = hif_drv;

	if (wilc->clients_count == 0)
		mutex_init(&wilc->deinit_lock);

	timer_setup(&vif->periodic_rssi, get_periodic_rssi, 0);
	mod_timer(&vif->periodic_rssi, jiffies + msecs_to_jiffies(5000));

	timer_setup(&hif_drv->scan_timer, timer_scan_cb, 0);
	timer_setup(&hif_drv->connect_timer, timer_connect_cb, 0);
	timer_setup(&hif_drv->remain_on_ch_timer, listen_timer_cb, 0);

	hif_drv->hif_state = HOST_IF_IDLE;

	hif_drv->p2p_timeout = 0;

	wilc->clients_count++;

	return 0;
}