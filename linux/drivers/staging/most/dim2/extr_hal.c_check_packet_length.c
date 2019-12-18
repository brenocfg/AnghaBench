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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ CDT1_BS_ISOC_MASK ; 
 scalar_t__ CDT3_BD_ISOC_MASK ; 
 scalar_t__ ISOC_DBR_FACTOR ; 

__attribute__((used)) static inline bool check_packet_length(u32 packet_length)
{
	u16 const max_size = ((u16)CDT3_BD_ISOC_MASK + 1u) / ISOC_DBR_FACTOR;

	if (packet_length <= 0)
		return false; /* too small */

	if (packet_length > max_size)
		return false; /* too big */

	if (packet_length - 1u > (u32)CDT1_BS_ISOC_MASK)
		return false; /* too big */

	return true;
}