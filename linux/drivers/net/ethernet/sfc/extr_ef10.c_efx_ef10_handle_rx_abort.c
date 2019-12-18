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
struct efx_rx_queue {unsigned int scatter_n; unsigned int removed_count; unsigned int ptr_mask; scalar_t__ scatter_len; TYPE_1__* efx; } ;
struct TYPE_4__ {int /*<<< orphan*/  n_rx_nodesc_trunc; } ;
struct TYPE_3__ {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFX_RX_PKT_DISCARD ; 
 int /*<<< orphan*/  efx_rx_packet (struct efx_rx_queue*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* efx_rx_queue_channel (struct efx_rx_queue*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static void efx_ef10_handle_rx_abort(struct efx_rx_queue *rx_queue)
{
	unsigned int rx_desc_ptr;

	netif_dbg(rx_queue->efx, hw, rx_queue->efx->net_dev,
		  "scattered RX aborted (dropping %u buffers)\n",
		  rx_queue->scatter_n);

	rx_desc_ptr = rx_queue->removed_count & rx_queue->ptr_mask;

	efx_rx_packet(rx_queue, rx_desc_ptr, rx_queue->scatter_n,
		      0, EFX_RX_PKT_DISCARD);

	rx_queue->removed_count += rx_queue->scatter_n;
	rx_queue->scatter_n = 0;
	rx_queue->scatter_len = 0;
	++efx_rx_queue_channel(rx_queue)->n_rx_nodesc_trunc;
}