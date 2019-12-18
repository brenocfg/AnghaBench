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
struct ucc_geth_private {int /*<<< orphan*/  napi; TYPE_2__* ug_info; int /*<<< orphan*/  ndev; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {TYPE_1__ uf_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ugeth_quiesce(struct ucc_geth_private *ugeth)
{
	/* Prevent any further xmits, plus detach the device. */
	netif_device_detach(ugeth->ndev);

	/* Wait for any current xmits to finish. */
	netif_tx_disable(ugeth->ndev);

	/* Disable the interrupt to avoid NAPI rescheduling. */
	disable_irq(ugeth->ug_info->uf_info.irq);

	/* Stop NAPI, and possibly wait for its completion. */
	napi_disable(&ugeth->napi);
}