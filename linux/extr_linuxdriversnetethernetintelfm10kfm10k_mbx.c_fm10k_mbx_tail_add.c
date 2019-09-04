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
typedef  int u16 ;
struct fm10k_mbx_info {int tail; int mbmem_len; } ;

/* Variables and functions */

__attribute__((used)) static u16 fm10k_mbx_tail_add(struct fm10k_mbx_info *mbx, u16 offset)
{
	u16 tail = (mbx->tail + offset + 1) & ((mbx->mbmem_len << 1) - 1);

	/* add/sub 1 because we cannot have offset 0 or all 1s */
	return (tail > mbx->tail) ? --tail : ++tail;
}