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
struct fm10k_mbx_info {int mbmem_len; } ;

/* Variables and functions */

__attribute__((used)) static u16 fm10k_mbx_index_len(struct fm10k_mbx_info *mbx, u16 head, u16 tail)
{
	u16 len = tail - head;

	/* we wrapped so subtract 2, one for index 0, one for all 1s index */
	if (len > tail)
		len -= 2;

	return len & ((mbx->mbmem_len << 1) - 1);
}