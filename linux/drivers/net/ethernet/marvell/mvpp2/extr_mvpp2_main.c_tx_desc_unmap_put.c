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
struct mvpp2_txq_pcpu {int dummy; } ;
struct mvpp2_tx_queue {int /*<<< orphan*/  pcpu; } ;
struct mvpp2_tx_desc {int dummy; } ;
struct mvpp2_port {TYPE_2__* dev; int /*<<< orphan*/  priv; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IS_TSO_HEADER (struct mvpp2_txq_pcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 unsigned int mvpp2_cpu_to_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_txdesc_dma_addr_get (struct mvpp2_port*,struct mvpp2_tx_desc*) ; 
 size_t mvpp2_txdesc_size_get (struct mvpp2_port*,struct mvpp2_tx_desc*) ; 
 int /*<<< orphan*/  mvpp2_txq_desc_put (struct mvpp2_tx_queue*) ; 
 struct mvpp2_txq_pcpu* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static inline void
tx_desc_unmap_put(struct mvpp2_port *port, struct mvpp2_tx_queue *txq,
		  struct mvpp2_tx_desc *desc)
{
	unsigned int thread = mvpp2_cpu_to_thread(port->priv, smp_processor_id());
	struct mvpp2_txq_pcpu *txq_pcpu = per_cpu_ptr(txq->pcpu, thread);

	dma_addr_t buf_dma_addr =
		mvpp2_txdesc_dma_addr_get(port, desc);
	size_t buf_sz =
		mvpp2_txdesc_size_get(port, desc);
	if (!IS_TSO_HEADER(txq_pcpu, buf_dma_addr))
		dma_unmap_single(port->dev->dev.parent, buf_dma_addr,
				 buf_sz, DMA_TO_DEVICE);
	mvpp2_txq_desc_put(txq);
}