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
struct port {int /*<<< orphan*/ * desc_tab; int /*<<< orphan*/  desc_tab_phys; int /*<<< orphan*/ ** tx_buff_tab; TYPE_1__* netdev; int /*<<< orphan*/ ** rx_buff_tab; } ;
struct desc {scalar_t__ data; } ;
typedef  int /*<<< orphan*/  buffer_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  RX_BUFF_SIZE ; 
 int RX_DESCS ; 
 int TX_DESCS ; 
 int /*<<< orphan*/ * dma_pool ; 
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_tx (struct port*,struct desc*) ; 
 int /*<<< orphan*/  free_buffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ports_open ; 
 struct desc* rx_desc_ptr (struct port*,int) ; 
 struct desc* tx_desc_ptr (struct port*,int) ; 

__attribute__((used)) static void destroy_queues(struct port *port)
{
	int i;

	if (port->desc_tab) {
		for (i = 0; i < RX_DESCS; i++) {
			struct desc *desc = rx_desc_ptr(port, i);
			buffer_t *buff = port->rx_buff_tab[i];
			if (buff) {
				dma_unmap_single(&port->netdev->dev,
						 desc->data - NET_IP_ALIGN,
						 RX_BUFF_SIZE, DMA_FROM_DEVICE);
				free_buffer(buff);
			}
		}
		for (i = 0; i < TX_DESCS; i++) {
			struct desc *desc = tx_desc_ptr(port, i);
			buffer_t *buff = port->tx_buff_tab[i];
			if (buff) {
				dma_unmap_tx(port, desc);
				free_buffer(buff);
			}
		}
		dma_pool_free(dma_pool, port->desc_tab, port->desc_tab_phys);
		port->desc_tab = NULL;
	}

	if (!ports_open && dma_pool) {
		dma_pool_destroy(dma_pool);
		dma_pool = NULL;
	}
}