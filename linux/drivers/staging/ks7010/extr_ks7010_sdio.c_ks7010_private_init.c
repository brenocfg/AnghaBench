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
struct TYPE_2__ {int /*<<< orphan*/  wakeup_request; int /*<<< orphan*/  doze_request; } ;
struct ks_wlan_private {char* firmware_version; TYPE_1__ sleepstatus; int /*<<< orphan*/  wstats; int /*<<< orphan*/  nstats; void* last_wakeup; void* last_doze; scalar_t__ version_size; struct net_device* net_dev; int /*<<< orphan*/  dev_state; struct ks_sdio_card* if_hw; } ;
struct ks_sdio_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_PREBOOT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostif_init (struct ks_wlan_private*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  ks7010_init_defaults (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  ks_wlan_net_start (struct net_device*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trx_device_init (struct ks_wlan_private*) ; 

__attribute__((used)) static void ks7010_private_init(struct ks_wlan_private *priv,
				struct ks_sdio_card *card,
				struct net_device *netdev)
{
	/* private memory initialize */
	priv->if_hw = card;

	priv->dev_state = DEVICE_STATE_PREBOOT;
	priv->net_dev = netdev;
	priv->firmware_version[0] = '\0';
	priv->version_size = 0;
	priv->last_doze = jiffies;
	priv->last_wakeup = jiffies;
	memset(&priv->nstats, 0, sizeof(priv->nstats));
	memset(&priv->wstats, 0, sizeof(priv->wstats));

	/* sleep mode */
	atomic_set(&priv->sleepstatus.doze_request, 0);
	atomic_set(&priv->sleepstatus.wakeup_request, 0);
	atomic_set(&priv->sleepstatus.wakeup_request, 0);

	trx_device_init(priv);
	hostif_init(priv);
	ks_wlan_net_start(netdev);
	ks7010_init_defaults(priv);
}