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
struct xgmac_dma_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  desc_set_buf_addr (struct xgmac_dma_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  desc_set_buf_len (struct xgmac_dma_desc*,int) ; 

__attribute__((used)) static inline void desc_set_buf_addr_and_size(struct xgmac_dma_desc *p,
					      u32 paddr, int len)
{
	desc_set_buf_len(p, len);
	desc_set_buf_addr(p, paddr, len);
}