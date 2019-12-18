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

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int) ; 
 scalar_t__ WIL_MAX_MPDU_OVERHEAD ; 

__attribute__((used)) static inline u32 wil_mtu2macbuf(u32 mtu)
{
	return ALIGN(mtu + WIL_MAX_MPDU_OVERHEAD, 8);
}