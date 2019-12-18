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
typedef  int u64 ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int MLX5_IB_MTT_READ ; 
 int MLX5_IB_MTT_WRITE ; 
 int ODP_DMA_ADDR_MASK ; 
 int ODP_READ_ALLOWED_BIT ; 
 int ODP_WRITE_ALLOWED_BIT ; 

__attribute__((used)) static u64 umem_dma_to_mtt(dma_addr_t umem_dma)
{
	u64 mtt_entry = umem_dma & ODP_DMA_ADDR_MASK;

	if (umem_dma & ODP_READ_ALLOWED_BIT)
		mtt_entry |= MLX5_IB_MTT_READ;
	if (umem_dma & ODP_WRITE_ALLOWED_BIT)
		mtt_entry |= MLX5_IB_MTT_WRITE;

	return mtt_entry;
}