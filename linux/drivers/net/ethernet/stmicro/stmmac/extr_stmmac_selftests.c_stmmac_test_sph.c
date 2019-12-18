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
struct TYPE_4__ {unsigned long rx_split_hdr_pkt_n; } ;
struct stmmac_priv {TYPE_2__ xstats; TYPE_1__* dev; int /*<<< orphan*/  sph; } ;
struct stmmac_packet_attrs {int tcp; int /*<<< orphan*/  dst; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int __stmmac_test_loopback (struct stmmac_priv*,struct stmmac_packet_attrs*) ; 

__attribute__((used)) static int stmmac_test_sph(struct stmmac_priv *priv)
{
	unsigned long cnt_end, cnt_start = priv->xstats.rx_split_hdr_pkt_n;
	struct stmmac_packet_attrs attr = { };
	int ret;

	if (!priv->sph)
		return -EOPNOTSUPP;

	/* Check for UDP first */
	attr.dst = priv->dev->dev_addr;
	attr.tcp = false;

	ret = __stmmac_test_loopback(priv, &attr);
	if (ret)
		return ret;

	cnt_end = priv->xstats.rx_split_hdr_pkt_n;
	if (cnt_end <= cnt_start)
		return -EINVAL;

	/* Check for TCP now */
	cnt_start = cnt_end;

	attr.dst = priv->dev->dev_addr;
	attr.tcp = true;

	ret = __stmmac_test_loopback(priv, &attr);
	if (ret)
		return ret;

	cnt_end = priv->xstats.rx_split_hdr_pkt_n;
	if (cnt_end <= cnt_start)
		return -EINVAL;

	return 0;
}