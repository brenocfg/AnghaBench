#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  enable; } ;
struct TYPE_4__ {int /*<<< orphan*/  rssen; } ;
struct stmmac_priv {TYPE_3__* dev; TYPE_2__ rss; TYPE_1__ dma_cap; } ;
struct stmmac_packet_attrs {int exp_hash; int sport; int dport; int /*<<< orphan*/  dst; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int __stmmac_test_loopback (struct stmmac_priv*,struct stmmac_packet_attrs*) ; 

__attribute__((used)) static int stmmac_test_rss(struct stmmac_priv *priv)
{
	struct stmmac_packet_attrs attr = { };

	if (!priv->dma_cap.rssen || !priv->rss.enable)
		return -EOPNOTSUPP;

	attr.dst = priv->dev->dev_addr;
	attr.exp_hash = true;
	attr.sport = 0x321;
	attr.dport = 0x123;

	return __stmmac_test_loopback(priv, &attr);
}