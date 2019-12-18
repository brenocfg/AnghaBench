#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct net_device {scalar_t__ dev_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* LedControlHandler ) (struct _adapter*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  smart_ps; int /*<<< orphan*/  power_mgnt; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* inirp_init ) (struct _adapter*) ;} ;
struct TYPE_5__ {scalar_t__ mac_addr; } ;
struct _adapter {int bup; int driver_stopped; int surprise_removed; int /*<<< orphan*/  mutex_start; TYPE_4__ ledpriv; TYPE_3__ registrypriv; TYPE_2__ dvobjpriv; TYPE_1__ eeprompriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  LED_CTL_NO_LINK ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  cbw40_enable ; 
 int /*<<< orphan*/  enable_video_mode (struct _adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct _adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  r8712_initmac ; 
 int /*<<< orphan*/  r8712_setMacAddr_cmd (struct _adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8712_set_ps_mode (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtl871x_hal_init (struct _adapter*) ; 
 scalar_t__ start_drv_threads (struct _adapter*) ; 
 int /*<<< orphan*/  start_drv_timers (struct _adapter*) ; 
 int /*<<< orphan*/  stub1 (struct _adapter*) ; 
 int /*<<< orphan*/  stub2 (struct _adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ video_mode ; 

__attribute__((used)) static int netdev_open(struct net_device *pnetdev)
{
	struct _adapter *padapter = netdev_priv(pnetdev);

	mutex_lock(&padapter->mutex_start);
	if (!padapter->bup) {
		padapter->driver_stopped = false;
		padapter->surprise_removed = false;
		padapter->bup = true;
		if (rtl871x_hal_init(padapter) != _SUCCESS)
			goto netdev_open_error;
		if (!r8712_initmac) {
			/* Use the mac address stored in the Efuse */
			memcpy(pnetdev->dev_addr,
			       padapter->eeprompriv.mac_addr, ETH_ALEN);
		} else {
			/* We have to inform f/w to use user-supplied MAC
			 * address.
			 */
			msleep(200);
			r8712_setMacAddr_cmd(padapter, (u8 *)pnetdev->dev_addr);
			/*
			 * The "myid" function will get the wifi mac address
			 * from eeprompriv structure instead of netdev
			 * structure. So, we have to overwrite the mac_addr
			 * stored in the eeprompriv structure. In this case,
			 * the real mac address won't be used anymore. So that,
			 * the eeprompriv.mac_addr should store the mac which
			 * users specify.
			 */
			memcpy(padapter->eeprompriv.mac_addr,
			       pnetdev->dev_addr, ETH_ALEN);
		}
		if (start_drv_threads(padapter) != _SUCCESS)
			goto netdev_open_error;
		if (!padapter->dvobjpriv.inirp_init)
			goto netdev_open_error;
		else
			padapter->dvobjpriv.inirp_init(padapter);
		r8712_set_ps_mode(padapter, padapter->registrypriv.power_mgnt,
				  padapter->registrypriv.smart_ps);
	}
	if (!netif_queue_stopped(pnetdev))
		netif_start_queue(pnetdev);
	else
		netif_wake_queue(pnetdev);

	if (video_mode)
		enable_video_mode(padapter, cbw40_enable);
	/* start driver mlme relation timer */
	start_drv_timers(padapter);
	padapter->ledpriv.LedControlHandler(padapter, LED_CTL_NO_LINK);
	mutex_unlock(&padapter->mutex_start);
	return 0;
netdev_open_error:
	padapter->bup = false;
	netif_carrier_off(pnetdev);
	netif_stop_queue(pnetdev);
	mutex_unlock(&padapter->mutex_start);
	return -1;
}