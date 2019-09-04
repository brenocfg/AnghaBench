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
struct hnae_ring {int dummy; } ;
typedef  enum hns_desc_type { ____Placeholder_hns_desc_type } hns_desc_type ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  fill_v2_desc_hw (struct hnae_ring*,void*,int,int,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void fill_v2_desc(struct hnae_ring *ring, void *priv,
			 int size, dma_addr_t dma, int frag_end,
			 int buf_num, enum hns_desc_type type, int mtu)
{
	fill_v2_desc_hw(ring, priv, size, size, dma, frag_end,
			buf_num, type, mtu);
}