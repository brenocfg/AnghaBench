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
typedef  scalar_t__ uint ;
typedef  scalar_t__ u64 ;
struct sitesurvey_ctrl {scalar_t__ last_tx_pkts; scalar_t__ last_rx_pkts; int traffic_busy; } ;
struct registry_priv {scalar_t__ busy_thresh; } ;
struct mlme_priv {struct sitesurvey_ctrl sitesurveyctrl; } ;
struct TYPE_4__ {scalar_t__ rx_pkts; } ;
struct TYPE_3__ {scalar_t__ tx_pkts; } ;
struct _adapter {TYPE_2__ recvpriv; TYPE_1__ xmitpriv; struct registry_priv registrypriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */

void _r8712_sitesurvey_ctrl_handler(struct _adapter *adapter)
{
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
	struct sitesurvey_ctrl	*psitesurveyctrl = &pmlmepriv->sitesurveyctrl;
	struct registry_priv	*pregistrypriv = &adapter->registrypriv;
	u64 current_tx_pkts;
	uint current_rx_pkts;

	current_tx_pkts = (adapter->xmitpriv.tx_pkts) -
			  (psitesurveyctrl->last_tx_pkts);
	current_rx_pkts = (adapter->recvpriv.rx_pkts) -
			  (psitesurveyctrl->last_rx_pkts);
	psitesurveyctrl->last_tx_pkts = adapter->xmitpriv.tx_pkts;
	psitesurveyctrl->last_rx_pkts = adapter->recvpriv.rx_pkts;
	if ((current_tx_pkts > pregistrypriv->busy_thresh) ||
	    (current_rx_pkts > pregistrypriv->busy_thresh))
		psitesurveyctrl->traffic_busy = true;
	else
		psitesurveyctrl->traffic_busy = false;
}