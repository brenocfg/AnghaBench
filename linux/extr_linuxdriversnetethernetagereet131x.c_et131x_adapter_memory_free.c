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
struct et131x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  et131x_rx_dma_memory_free (struct et131x_adapter*) ; 
 int /*<<< orphan*/  et131x_tx_dma_memory_free (struct et131x_adapter*) ; 

__attribute__((used)) static void et131x_adapter_memory_free(struct et131x_adapter *adapter)
{
	et131x_tx_dma_memory_free(adapter);
	et131x_rx_dma_memory_free(adapter);
}