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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_txbuffer_desc_add_high_with_offset(__le32 *pbd, u8 off,
							  u32 val, bool dma64)
{
	if (dma64)
		*(pbd + 4 * off + 2) = cpu_to_le32(val);
	else
		*(pbd + 4 * off + 2) = 0;
}