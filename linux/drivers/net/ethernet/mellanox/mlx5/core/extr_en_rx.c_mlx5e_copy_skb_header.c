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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct mlx5e_dma_info {scalar_t__ addr; int /*<<< orphan*/  page; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (struct device*,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 void* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,void const*,unsigned int) ; 

__attribute__((used)) static inline void
mlx5e_copy_skb_header(struct device *pdev, struct sk_buff *skb,
		      struct mlx5e_dma_info *dma_info,
		      int offset_from, u32 headlen)
{
	const void *from = page_address(dma_info->page) + offset_from;
	/* Aligning len to sizeof(long) optimizes memcpy performance */
	unsigned int len = ALIGN(headlen, sizeof(long));

	dma_sync_single_for_cpu(pdev, dma_info->addr + offset_from, len,
				DMA_FROM_DEVICE);
	skb_copy_to_linear_data(skb, from, len);
}