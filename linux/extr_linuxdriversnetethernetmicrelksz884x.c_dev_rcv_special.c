#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  error; scalar_t__ first_desc; scalar_t__ last_desc; int /*<<< orphan*/  src_port; scalar_t__ hw_owned; } ;
union desc_stat {int data; TYPE_4__ rx; } ;
struct net_device {int dummy; } ;
struct ksz_desc_info {int alloc; int next; int mask; struct ksz_desc* ring; } ;
struct ksz_hw {int dev_count; TYPE_3__* port_info; struct ksz_desc_info rx_desc_info; } ;
struct ksz_desc {TYPE_2__* phw; } ;
struct TYPE_10__ {int /*<<< orphan*/ * counter; } ;
struct dev_priv {TYPE_5__ port; } ;
struct dev_info {struct ksz_hw hw; } ;
struct TYPE_8__ {struct net_device* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_7__ {TYPE_1__ ctrl; } ;

/* Variables and functions */
 int HW_TO_DEV_PORT (int /*<<< orphan*/ ) ; 
 int KS_DESC_RX_ERROR_COND ; 
 int KS_DESC_RX_ERROR_TOO_LONG ; 
 size_t OID_COUNTER_RCV_ERROR ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  release_desc (struct ksz_desc*) ; 
 scalar_t__ rx_proc (struct net_device*,struct ksz_hw*,struct ksz_desc*,union desc_stat) ; 

__attribute__((used)) static int dev_rcv_special(struct dev_info *hw_priv)
{
	int next;
	union desc_stat status;
	struct ksz_hw *hw = &hw_priv->hw;
	struct net_device *dev = hw->port_info[0].pdev;
	struct ksz_desc_info *info = &hw->rx_desc_info;
	int left = info->alloc;
	struct ksz_desc *desc;
	int received = 0;

	next = info->next;
	while (left--) {
		/* Get next descriptor which is not hardware owned. */
		desc = &info->ring[next];
		status.data = le32_to_cpu(desc->phw->ctrl.data);
		if (status.rx.hw_owned)
			break;

		if (hw->dev_count > 1) {
			/* Get received port number. */
			int p = HW_TO_DEV_PORT(status.rx.src_port);

			dev = hw->port_info[p].pdev;
			if (!netif_running(dev))
				goto release_packet;
		}

		/* Status valid only when last descriptor bit is set. */
		if (status.rx.last_desc && status.rx.first_desc) {
			/*
			 * Receive without error.  With receive errors
			 * disabled, packets with receive errors will be
			 * dropped, so no need to check the error bit.
			 */
			if (!status.rx.error || (status.data &
					KS_DESC_RX_ERROR_COND) ==
					KS_DESC_RX_ERROR_TOO_LONG) {
				if (rx_proc(dev, hw, desc, status))
					goto release_packet;
				received++;
			} else {
				struct dev_priv *priv = netdev_priv(dev);

				/* Update receive error statistics. */
				priv->port.counter[OID_COUNTER_RCV_ERROR]++;
			}
		}

release_packet:
		release_desc(desc);
		next++;
		next &= info->mask;
	}
	info->next = next;

	return received;
}