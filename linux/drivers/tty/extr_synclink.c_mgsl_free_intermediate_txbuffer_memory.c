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
struct mgsl_struct {int num_tx_holding_buffers; scalar_t__ tx_holding_count; scalar_t__ put_tx_holding_index; scalar_t__ get_tx_holding_index; TYPE_1__* tx_holding_buffers; } ;
struct TYPE_2__ {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mgsl_free_intermediate_txbuffer_memory(struct mgsl_struct *info)
{
	int i;

	for ( i=0; i<info->num_tx_holding_buffers; ++i ) {
		kfree(info->tx_holding_buffers[i].buffer);
		info->tx_holding_buffers[i].buffer = NULL;
	}

	info->get_tx_holding_index = 0;
	info->put_tx_holding_index = 0;
	info->tx_holding_count = 0;

}