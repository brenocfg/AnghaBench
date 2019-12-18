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
struct ef4_nic {TYPE_1__* pci_dev; } ;
struct ef4_buffer {int /*<<< orphan*/ * addr; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ef4_nic_free_buffer(struct ef4_nic *efx, struct ef4_buffer *buffer)
{
	if (buffer->addr) {
		dma_free_coherent(&efx->pci_dev->dev, buffer->len,
				  buffer->addr, buffer->dma_addr);
		buffer->addr = NULL;
	}
}