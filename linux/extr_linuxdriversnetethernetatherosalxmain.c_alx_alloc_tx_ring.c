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
struct alx_txd {int dummy; } ;
struct alx_tx_queue {int count; scalar_t__ tpd_dma; scalar_t__ tpd; int /*<<< orphan*/  bufs; } ;
struct TYPE_2__ {scalar_t__ dma; scalar_t__ virt; } ;
struct alx_priv {TYPE_1__ descmem; } ;
struct alx_buffer {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alx_alloc_tx_ring(struct alx_priv *alx, struct alx_tx_queue *txq,
			     int offset)
{
	txq->bufs = kcalloc(txq->count, sizeof(struct alx_buffer), GFP_KERNEL);
	if (!txq->bufs)
		return -ENOMEM;

	txq->tpd = alx->descmem.virt + offset;
	txq->tpd_dma = alx->descmem.dma + offset;
	offset += sizeof(struct alx_txd) * txq->count;

	return offset;
}