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
struct TYPE_2__ {int /*<<< orphan*/  (* LedControlHandler ) (struct _adapter*,int /*<<< orphan*/ ) ;} ;
struct _adapter {TYPE_1__ ledpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LED_CTL_POWER_OFF ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct _adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  r8712_disassoc_cmd (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_free_assoc_resources (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_free_network_queue (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_ind_disconnect (struct _adapter*) ; 
 int /*<<< orphan*/  stub1 (struct _adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netdev_close(struct net_device *pnetdev)
{
	struct _adapter *padapter = netdev_priv(pnetdev);

	/* Close LED*/
	padapter->ledpriv.LedControlHandler(padapter, LED_CTL_POWER_OFF);
	msleep(200);

	/*s1.*/
	if (pnetdev) {
		if (!netif_queue_stopped(pnetdev))
			netif_stop_queue(pnetdev);
	}
	/*s2.*/
	/*s2-1.  issue disassoc_cmd to fw*/
	r8712_disassoc_cmd(padapter);
	/*s2-2.  indicate disconnect to os*/
	r8712_ind_disconnect(padapter);
	/*s2-3.*/
	r8712_free_assoc_resources(padapter);
	/*s2-4.*/
	r8712_free_network_queue(padapter);
	return 0;
}