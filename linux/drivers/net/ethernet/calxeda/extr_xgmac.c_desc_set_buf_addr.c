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
typedef  scalar_t__ u32 ;
struct xgmac_dma_desc {void* buf2_addr; void* buf1_addr; } ;

/* Variables and functions */
 int MAX_DESC_BUF_SZ ; 
 void* cpu_to_le32 (scalar_t__) ; 

__attribute__((used)) static inline void desc_set_buf_addr(struct xgmac_dma_desc *p,
				     u32 paddr, int len)
{
	p->buf1_addr = cpu_to_le32(paddr);
	if (len > MAX_DESC_BUF_SZ)
		p->buf2_addr = cpu_to_le32(paddr + MAX_DESC_BUF_SZ);
}