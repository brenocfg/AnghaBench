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
struct rx_device_buffer {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {size_t qhead; struct rx_device_buffer* rx_dev_buff; } ;
struct ks_wlan_private {scalar_t__ dev_state; int /*<<< orphan*/  rx_bh_task; TYPE_1__ rx_dev; } ;

/* Variables and functions */
 scalar_t__ DEVICE_STATE_BOOT ; 
 int /*<<< orphan*/  hostif_receive (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_rxqhead (struct ks_wlan_private*) ; 
 scalar_t__ rxq_has_space (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rx_event_task(unsigned long dev)
{
	struct ks_wlan_private *priv = (struct ks_wlan_private *)dev;
	struct rx_device_buffer *rp;

	if (rxq_has_space(priv) && priv->dev_state >= DEVICE_STATE_BOOT) {
		rp = &priv->rx_dev.rx_dev_buff[priv->rx_dev.qhead];
		hostif_receive(priv, rp->data, rp->size);
		inc_rxqhead(priv);

		if (rxq_has_space(priv))
			tasklet_schedule(&priv->rx_bh_task);
	}
}