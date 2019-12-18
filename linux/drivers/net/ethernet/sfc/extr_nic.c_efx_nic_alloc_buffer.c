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
struct efx_nic {TYPE_1__* pci_dev; } ;
struct efx_buffer {unsigned int len; int /*<<< orphan*/  addr; int /*<<< orphan*/  dma_addr; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int efx_nic_alloc_buffer(struct efx_nic *efx, struct efx_buffer *buffer,
			 unsigned int len, gfp_t gfp_flags)
{
	buffer->addr = dma_alloc_coherent(&efx->pci_dev->dev, len,
					  &buffer->dma_addr, gfp_flags);
	if (!buffer->addr)
		return -ENOMEM;
	buffer->len = len;
	return 0;
}