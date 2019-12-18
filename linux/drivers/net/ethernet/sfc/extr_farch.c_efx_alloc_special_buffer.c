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
typedef  int /*<<< orphan*/  u64 ;
struct siena_nic_data {scalar_t__ vf_buftbl_base; } ;
struct TYPE_2__ {unsigned int dma_addr; int /*<<< orphan*/  addr; } ;
struct efx_special_buffer {unsigned int entries; scalar_t__ index; TYPE_1__ buf; } ;
struct efx_nic {scalar_t__ next_buffer_table; int /*<<< orphan*/  net_dev; struct siena_nic_data* nic_data; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int EFX_BUF_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ efx_nic_alloc_buffer (struct efx_nic*,TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ efx_siena_sriov_enabled (struct efx_nic*) ; 
 int /*<<< orphan*/  netif_dbg (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 
 scalar_t__ virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_alloc_special_buffer(struct efx_nic *efx,
				    struct efx_special_buffer *buffer,
				    unsigned int len)
{
#ifdef CONFIG_SFC_SRIOV
	struct siena_nic_data *nic_data = efx->nic_data;
#endif
	len = ALIGN(len, EFX_BUF_SIZE);

	if (efx_nic_alloc_buffer(efx, &buffer->buf, len, GFP_KERNEL))
		return -ENOMEM;
	buffer->entries = len / EFX_BUF_SIZE;
	BUG_ON(buffer->buf.dma_addr & (EFX_BUF_SIZE - 1));

	/* Select new buffer ID */
	buffer->index = efx->next_buffer_table;
	efx->next_buffer_table += buffer->entries;
#ifdef CONFIG_SFC_SRIOV
	BUG_ON(efx_siena_sriov_enabled(efx) &&
	       nic_data->vf_buftbl_base < efx->next_buffer_table);
#endif

	netif_dbg(efx, probe, efx->net_dev,
		  "allocating special buffers %d-%d at %llx+%x "
		  "(virt %p phys %llx)\n", buffer->index,
		  buffer->index + buffer->entries - 1,
		  (u64)buffer->buf.dma_addr, len,
		  buffer->buf.addr, (u64)virt_to_phys(buffer->buf.addr));

	return 0;
}