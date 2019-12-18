#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct efx_rx_queue {int ptr_mask; int /*<<< orphan*/  rxd; struct efx_nic* efx; } ;
struct efx_nic {int dummy; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 int efx_alloc_special_buffer (struct efx_nic*,int /*<<< orphan*/ *,unsigned int) ; 

int efx_farch_rx_probe(struct efx_rx_queue *rx_queue)
{
	struct efx_nic *efx = rx_queue->efx;
	unsigned entries;

	entries = rx_queue->ptr_mask + 1;
	return efx_alloc_special_buffer(efx, &rx_queue->rxd,
					entries * sizeof(efx_qword_t));
}