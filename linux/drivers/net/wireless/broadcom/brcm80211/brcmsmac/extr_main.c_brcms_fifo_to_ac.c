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
typedef  size_t u8 ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t*) ; 
 size_t IEEE80211_AC_BE ; 
 size_t* fifo_to_ac_mapping ; 

__attribute__((used)) static u8 brcms_fifo_to_ac(u8 fifo)
{
	if (fifo >= ARRAY_SIZE(fifo_to_ac_mapping))
		return IEEE80211_AC_BE;
	return fifo_to_ac_mapping[fifo];
}