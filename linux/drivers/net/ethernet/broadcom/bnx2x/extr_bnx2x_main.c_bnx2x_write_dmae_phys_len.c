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
typedef  int u32 ;
struct bnx2x {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int DMAE_LEN32_WR_MAX (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_write_dmae (struct bnx2x*,scalar_t__,int,int) ; 

__attribute__((used)) static void bnx2x_write_dmae_phys_len(struct bnx2x *bp, dma_addr_t phys_addr,
				      u32 addr, u32 len)
{
	int dmae_wr_max = DMAE_LEN32_WR_MAX(bp);
	int offset = 0;

	while (len > dmae_wr_max) {
		bnx2x_write_dmae(bp, phys_addr + offset,
				 addr + offset, dmae_wr_max);
		offset += dmae_wr_max * 4;
		len -= dmae_wr_max;
	}

	bnx2x_write_dmae(bp, phys_addr + offset, addr + offset, len);
}