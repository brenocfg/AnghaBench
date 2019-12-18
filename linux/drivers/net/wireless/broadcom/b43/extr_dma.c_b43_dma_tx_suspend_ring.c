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
struct b43_dmaring {TYPE_1__* ops; int /*<<< orphan*/  tx; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tx_suspend ) (struct b43_dmaring*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  stub1 (struct b43_dmaring*) ; 

__attribute__((used)) static void b43_dma_tx_suspend_ring(struct b43_dmaring *ring)
{
	B43_WARN_ON(!ring->tx);
	ring->ops->tx_suspend(ring);
}