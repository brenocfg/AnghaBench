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
struct tx_device_buffer {int /*<<< orphan*/  skb; int /*<<< orphan*/  (* complete_handler ) (struct ks_wlan_private*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sendp; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {size_t qhead; struct tx_device_buffer* tx_dev_buff; } ;
struct TYPE_3__ {int /*<<< orphan*/  status; } ;
struct ks_wlan_private {scalar_t__ dev_state; int /*<<< orphan*/  rw_dwork; int /*<<< orphan*/  wq; int /*<<< orphan*/  net_dev; TYPE_2__ tx_dev; TYPE_1__ psstatus; } ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_BOOT ; 
 scalar_t__ PS_SNOOZE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inc_txqhead (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct ks_wlan_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ txq_has_space (struct ks_wlan_private*) ; 
 int write_to_device (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx_device_task(struct ks_wlan_private *priv)
{
	struct tx_device_buffer *sp;
	int ret;

	if (!txq_has_space(priv) ||
	    atomic_read(&priv->psstatus.status) == PS_SNOOZE)
		return;

	sp = &priv->tx_dev.tx_dev_buff[priv->tx_dev.qhead];
	if (priv->dev_state >= DEVICE_STATE_BOOT) {
		ret = write_to_device(priv, sp->sendp, sp->size);
		if (ret) {
			netdev_err(priv->net_dev,
				   "write_to_device error !!(%d)\n", ret);
			queue_delayed_work(priv->wq, &priv->rw_dwork, 1);
			return;
		}
	}
	kfree(sp->sendp);
	if (sp->complete_handler)	/* TX Complete */
		(*sp->complete_handler)(priv, sp->skb);
	inc_txqhead(priv);

	if (txq_has_space(priv))
		queue_delayed_work(priv->wq, &priv->rw_dwork, 0);
}