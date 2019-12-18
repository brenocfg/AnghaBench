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
struct TYPE_3__ {int /*<<< orphan*/  buf_count; } ;
struct TYPE_4__ {TYPE_1__ in_buf_pool; } ;
struct qeth_card {TYPE_2__ qdio; } ;
struct net_device {struct qeth_card* ml_priv; } ;
struct ethtool_ringparam {void* tx_pending; scalar_t__ rx_jumbo_pending; scalar_t__ rx_mini_pending; int /*<<< orphan*/  rx_pending; void* tx_max_pending; scalar_t__ rx_jumbo_max_pending; scalar_t__ rx_mini_max_pending; void* rx_max_pending; } ;

/* Variables and functions */
 void* QDIO_MAX_BUFFERS_PER_Q ; 

__attribute__((used)) static void qeth_get_ringparam(struct net_device *dev,
			       struct ethtool_ringparam *param)
{
	struct qeth_card *card = dev->ml_priv;

	param->rx_max_pending = QDIO_MAX_BUFFERS_PER_Q;
	param->rx_mini_max_pending = 0;
	param->rx_jumbo_max_pending = 0;
	param->tx_max_pending = QDIO_MAX_BUFFERS_PER_Q;

	param->rx_pending = card->qdio.in_buf_pool.buf_count;
	param->rx_mini_pending = 0;
	param->rx_jumbo_pending = 0;
	param->tx_pending = QDIO_MAX_BUFFERS_PER_Q;
}