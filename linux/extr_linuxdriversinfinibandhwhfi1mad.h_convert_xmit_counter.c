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
typedef  int u64 ;
typedef  int u16 ;

/* Variables and functions */
 int DECIMAL_FACTORING ; 
 int FACTOR_LINK_WIDTH ; 

__attribute__((used)) static inline u64 convert_xmit_counter(u64 xmit_wait_val, u16 link_width,
				       u16 link_speed)
{
	return (xmit_wait_val * 2 * (FACTOR_LINK_WIDTH / link_width)
		 * link_speed) / DECIMAL_FACTORING;
}