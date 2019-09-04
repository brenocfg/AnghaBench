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
struct xgmac_dma_desc {int /*<<< orphan*/  buf_size; } ;

/* Variables and functions */
 int DESC_BUFFER1_SZ_MASK ; 
 int DESC_BUFFER2_SZ_MASK ; 
 int DESC_BUFFER2_SZ_OFFSET ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int desc_get_buf_len(struct xgmac_dma_desc *p)
{
	u32 len = le32_to_cpu(p->buf_size);
	return (len & DESC_BUFFER1_SZ_MASK) +
		((len & DESC_BUFFER2_SZ_MASK) >> DESC_BUFFER2_SZ_OFFSET);
}