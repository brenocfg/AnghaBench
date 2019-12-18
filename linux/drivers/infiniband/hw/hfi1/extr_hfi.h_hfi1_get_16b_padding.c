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

/* Variables and functions */
 int SIZE_OF_CRC ; 
 int SIZE_OF_LT ; 

__attribute__((used)) static inline int hfi1_get_16b_padding(u32 hdr_size, u32 payload)
{
	return -(hdr_size + payload + (SIZE_OF_CRC << 2) +
		     SIZE_OF_LT) & 0x7;
}