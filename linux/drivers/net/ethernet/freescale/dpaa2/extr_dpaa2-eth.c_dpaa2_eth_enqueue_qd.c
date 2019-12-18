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
typedef  int /*<<< orphan*/  u8 ;
struct dpaa2_fd {int dummy; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  tx_qdid; } ;
struct dpaa2_eth_fq {int /*<<< orphan*/  tx_qdbin; TYPE_1__* channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  dpio; } ;

/* Variables and functions */
 int dpaa2_io_service_enqueue_qd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dpaa2_fd*) ; 

__attribute__((used)) static inline int dpaa2_eth_enqueue_qd(struct dpaa2_eth_priv *priv,
				       struct dpaa2_eth_fq *fq,
				       struct dpaa2_fd *fd, u8 prio)
{
	return dpaa2_io_service_enqueue_qd(fq->channel->dpio,
					   priv->tx_qdid, prio,
					   fq->tx_qdbin, fd);
}