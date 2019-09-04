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

/* Variables and functions */
 unsigned char CMOS_READ (scalar_t__) ; 
 scalar_t__ NVRAM_FIRST_BYTE ; 

unsigned char __nvram_read_byte(int i)
{
	return CMOS_READ(NVRAM_FIRST_BYTE + i);
}