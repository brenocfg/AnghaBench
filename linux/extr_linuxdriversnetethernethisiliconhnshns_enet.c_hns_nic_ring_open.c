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
struct net_device {int dummy; } ;
struct hns_nic_priv {TYPE_3__* ring_data; struct hnae_handle* ae_handle; } ;
struct hnae_handle {TYPE_2__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  irq; } ;
struct TYPE_7__ {TYPE_4__* ring; int /*<<< orphan*/  napi; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* toggle_ring_irq ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct hns_nic_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_nic_ring_open(struct net_device *netdev, int idx)
{
	struct hns_nic_priv *priv = netdev_priv(netdev);
	struct hnae_handle *h = priv->ae_handle;

	napi_enable(&priv->ring_data[idx].napi);

	enable_irq(priv->ring_data[idx].ring->irq);
	h->dev->ops->toggle_ring_irq(priv->ring_data[idx].ring, 0);

	return 0;
}