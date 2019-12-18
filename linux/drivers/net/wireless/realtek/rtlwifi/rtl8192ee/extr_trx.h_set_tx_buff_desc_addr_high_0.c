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
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_tx_buff_desc_addr_high_0(__le32 *pdesc, u32 val,
						bool dma64)
{
	if (dma64)
		*(pdesc + 2) = cpu_to_le32(val);
	else
		*(pdesc + 2) = 0;
}