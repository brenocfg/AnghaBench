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

__attribute__((used)) static inline void set_rx_buffer_physical_high(__le32 *__rx_status_desc,
					       u32 __val, bool dma64)
{
	if (dma64)
		*(__rx_status_desc + 2) = cpu_to_le32(__val);
	else
		*(__rx_status_desc + 2) = 0;
}