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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int HL_QUEUE_LENGTH ; 

inline u32 hl_hw_queue_add_ptr(u32 ptr, u16 val)
{
	ptr += val;
	ptr &= ((HL_QUEUE_LENGTH << 1) - 1);
	return ptr;
}