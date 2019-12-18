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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct efx_tx_queue {int ptr_mask; TYPE_1__ txd; int /*<<< orphan*/  efx; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int efx_nic_alloc_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_ef10_tx_probe(struct efx_tx_queue *tx_queue)
{
	return efx_nic_alloc_buffer(tx_queue->efx, &tx_queue->txd.buf,
				    (tx_queue->ptr_mask + 1) *
				    sizeof(efx_qword_t),
				    GFP_KERNEL);
}