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
struct stmmac_priv {TYPE_1__* dev; } ;
struct stmmac_packet_attrs {int /*<<< orphan*/  dst; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int __stmmac_test_loopback (struct stmmac_priv*,struct stmmac_packet_attrs*) ; 

__attribute__((used)) static int stmmac_test_mac_loopback(struct stmmac_priv *priv)
{
	struct stmmac_packet_attrs attr = { };

	attr.dst = priv->dev->dev_addr;
	return __stmmac_test_loopback(priv, &attr);
}