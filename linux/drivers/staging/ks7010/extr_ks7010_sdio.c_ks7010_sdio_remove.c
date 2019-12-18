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
struct sdio_func {int dummy; } ;
struct ks_wlan_private {int /*<<< orphan*/  net_dev; scalar_t__ wq; } ;
struct ks_sdio_card {struct ks_wlan_private* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_ENABLE_REG ; 
 int /*<<< orphan*/  INT_PENDING_REG ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostif_exit (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  kfree (struct ks_sdio_card*) ; 
 int /*<<< orphan*/  ks_wlan_net_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 struct ks_sdio_card* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_writeb (struct sdio_func*,int,int /*<<< orphan*/ ,int*) ; 
 int send_stop_request (struct sdio_func*) ; 
 int /*<<< orphan*/  trx_device_exit (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ks7010_sdio_remove(struct sdio_func *func)
{
	int ret;
	struct ks_sdio_card *card;
	struct ks_wlan_private *priv;

	card = sdio_get_drvdata(func);

	if (!card)
		return;

	priv = card->priv;
	if (!priv)
		goto err_free_card;

	ks_wlan_net_stop(priv->net_dev);

	/* interrupt disable */
	sdio_claim_host(func);
	sdio_writeb(func, 0, INT_ENABLE_REG, &ret);
	sdio_writeb(func, 0xff, INT_PENDING_REG, &ret);
	sdio_release_host(func);

	ret = send_stop_request(func);
	if (ret)	/* memory allocation failure */
		goto err_free_card;

	if (priv->wq) {
		flush_workqueue(priv->wq);
		destroy_workqueue(priv->wq);
	}

	hostif_exit(priv);

	unregister_netdev(priv->net_dev);

	trx_device_exit(priv);
	free_netdev(priv->net_dev);
	card->priv = NULL;

	sdio_claim_host(func);
	sdio_release_irq(func);
	sdio_disable_func(func);
	sdio_release_host(func);
err_free_card:
	sdio_set_drvdata(func, NULL);
	kfree(card);
}