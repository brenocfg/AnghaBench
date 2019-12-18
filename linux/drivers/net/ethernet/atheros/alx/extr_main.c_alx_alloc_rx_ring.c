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
struct alx_rx_queue {int count; scalar_t__ rfd_dma; scalar_t__ rfd; scalar_t__ rrd_dma; scalar_t__ rrd; int /*<<< orphan*/  bufs; } ;
struct alx_rrd {int dummy; } ;
struct alx_rfd {int dummy; } ;
struct TYPE_2__ {scalar_t__ dma; scalar_t__ virt; } ;
struct alx_priv {TYPE_1__ descmem; } ;
struct alx_buffer {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alx_alloc_rx_ring(struct alx_priv *alx, struct alx_rx_queue *rxq,
			     int offset)
{
	rxq->bufs = kcalloc(rxq->count, sizeof(struct alx_buffer), GFP_KERNEL);
	if (!rxq->bufs)
		return -ENOMEM;

	rxq->rrd = alx->descmem.virt + offset;
	rxq->rrd_dma = alx->descmem.dma + offset;
	offset += sizeof(struct alx_rrd) * rxq->count;

	rxq->rfd = alx->descmem.virt + offset;
	rxq->rfd_dma = alx->descmem.dma + offset;
	offset += sizeof(struct alx_rfd) * rxq->count;

	return offset;
}