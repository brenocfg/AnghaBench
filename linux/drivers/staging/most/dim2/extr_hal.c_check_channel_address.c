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
 scalar_t__ CAT_CL_MASK ; 

__attribute__((used)) static inline bool check_channel_address(u32 ch_address)
{
	return ch_address > 0 && (ch_address % 2) == 0 &&
	       (ch_address / 2) <= (u32)CAT_CL_MASK;
}