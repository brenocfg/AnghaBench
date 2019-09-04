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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u16 ;
struct pcnet32_private {int /*<<< orphan*/  napi; TYPE_1__* a; } ;
struct net_device {int /*<<< orphan*/  base_addr; } ;
struct TYPE_2__ {int (* read_csr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_csr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CSR3 ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct pcnet32_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pcnet32_netif_start(struct net_device *dev)
{
	struct pcnet32_private *lp = netdev_priv(dev);
	ulong ioaddr = dev->base_addr;
	u16 val;

	netif_wake_queue(dev);
	val = lp->a->read_csr(ioaddr, CSR3);
	val &= 0x00ff;
	lp->a->write_csr(ioaddr, CSR3, val);
	napi_enable(&lp->napi);
}