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
typedef  int /*<<< orphan*/  u16 ;
struct stmmac_priv {int dma_buf_sz; TYPE_1__* dev; } ;
struct stmmac_packet_attrs {int /*<<< orphan*/  queue_mapping; scalar_t__ max_size; int /*<<< orphan*/  dst; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ ETH_FCS_LEN ; 
 int __stmmac_test_loopback (struct stmmac_priv*,struct stmmac_packet_attrs*) ; 

__attribute__((used)) static int __stmmac_test_jumbo(struct stmmac_priv *priv, u16 queue)
{
	struct stmmac_packet_attrs attr = { };
	int size = priv->dma_buf_sz;

	attr.dst = priv->dev->dev_addr;
	attr.max_size = size - ETH_FCS_LEN;
	attr.queue_mapping = queue;

	return __stmmac_test_loopback(priv, &attr);
}