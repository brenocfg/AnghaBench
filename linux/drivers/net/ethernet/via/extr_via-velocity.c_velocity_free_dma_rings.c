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
struct TYPE_6__ {int /*<<< orphan*/  pool_dma; int /*<<< orphan*/  ring; } ;
struct TYPE_5__ {int numq; } ;
struct TYPE_4__ {int numrx; int numtx; } ;
struct velocity_info {TYPE_3__ rx; int /*<<< orphan*/  dev; TYPE_2__ tx; TYPE_1__ options; } ;
struct tx_desc {int dummy; } ;
struct rx_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void velocity_free_dma_rings(struct velocity_info *vptr)
{
	const int size = vptr->options.numrx * sizeof(struct rx_desc) +
		vptr->options.numtx * sizeof(struct tx_desc) * vptr->tx.numq;

	dma_free_coherent(vptr->dev, size, vptr->rx.ring, vptr->rx.pool_dma);
}