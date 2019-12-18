#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct rxf_desc {int dummy; } ;
struct TYPE_8__ {int memsz; scalar_t__ pktsz; } ;
struct TYPE_5__ {TYPE_4__ m; } ;
struct TYPE_6__ {TYPE_4__ m; } ;
struct bdx_priv {TYPE_3__* ndev; TYPE_1__ rxf_fifo0; int /*<<< orphan*/  rxdb; int /*<<< orphan*/  rxf_size; int /*<<< orphan*/  rxd_size; TYPE_2__ rxd_fifo0; } ;
struct TYPE_7__ {scalar_t__ mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ENTER ; 
 scalar_t__ VLAN_ETH_HLEN ; 
 scalar_t__ bdx_fifo_init (struct bdx_priv*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdx_rxdb_create (int) ; 
 int /*<<< orphan*/  netdev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  regRXD_CFG0_0 ; 
 int /*<<< orphan*/  regRXD_CFG1_0 ; 
 int /*<<< orphan*/  regRXD_RPTR_0 ; 
 int /*<<< orphan*/  regRXD_WPTR_0 ; 
 int /*<<< orphan*/  regRXF_CFG0_0 ; 
 int /*<<< orphan*/  regRXF_CFG1_0 ; 
 int /*<<< orphan*/  regRXF_RPTR_0 ; 
 int /*<<< orphan*/  regRXF_WPTR_0 ; 

__attribute__((used)) static int bdx_rx_init(struct bdx_priv *priv)
{
	ENTER;

	if (bdx_fifo_init(priv, &priv->rxd_fifo0.m, priv->rxd_size,
			  regRXD_CFG0_0, regRXD_CFG1_0,
			  regRXD_RPTR_0, regRXD_WPTR_0))
		goto err_mem;
	if (bdx_fifo_init(priv, &priv->rxf_fifo0.m, priv->rxf_size,
			  regRXF_CFG0_0, regRXF_CFG1_0,
			  regRXF_RPTR_0, regRXF_WPTR_0))
		goto err_mem;
	priv->rxdb = bdx_rxdb_create(priv->rxf_fifo0.m.memsz /
				     sizeof(struct rxf_desc));
	if (!priv->rxdb)
		goto err_mem;

	priv->rxf_fifo0.m.pktsz = priv->ndev->mtu + VLAN_ETH_HLEN;
	return 0;

err_mem:
	netdev_err(priv->ndev, "Rx init failed\n");
	return -ENOMEM;
}