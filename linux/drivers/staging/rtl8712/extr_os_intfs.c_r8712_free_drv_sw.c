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
struct net_device {int dummy; } ;
struct _adapter {int /*<<< orphan*/  recvpriv; int /*<<< orphan*/  stapriv; int /*<<< orphan*/  xmitpriv; int /*<<< orphan*/  mlmepriv; int /*<<< orphan*/  evtpriv; int /*<<< orphan*/  cmdpriv; struct net_device* pnetdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  _free_xmit_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _r8712_free_recv_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _r8712_free_sta_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mp871xdeinit (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_DeInitSwLeds (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_free_cmd_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8712_free_evt_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r8712_free_io_queue (struct _adapter*) ; 
 int /*<<< orphan*/  r8712_free_mlme_priv (int /*<<< orphan*/ *) ; 

void r8712_free_drv_sw(struct _adapter *padapter)
{
	struct net_device *pnetdev = padapter->pnetdev;

	r8712_free_cmd_priv(&padapter->cmdpriv);
	r8712_free_evt_priv(&padapter->evtpriv);
	r8712_DeInitSwLeds(padapter);
	r8712_free_mlme_priv(&padapter->mlmepriv);
	r8712_free_io_queue(padapter);
	_free_xmit_priv(&padapter->xmitpriv);
	_r8712_free_sta_priv(&padapter->stapriv);
	_r8712_free_recv_priv(&padapter->recvpriv);
	mp871xdeinit(padapter);
	if (pnetdev)
		free_netdev(pnetdev);
}