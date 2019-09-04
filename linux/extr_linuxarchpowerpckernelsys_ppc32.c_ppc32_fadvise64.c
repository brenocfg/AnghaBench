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
typedef  int u32 ;

/* Variables and functions */
 long ksys_fadvise64_64 (int,int,size_t,int) ; 

long ppc32_fadvise64(int fd, u32 unused, u32 offset_high, u32 offset_low,
		     size_t len, int advice)
{
	return ksys_fadvise64_64(fd, (u64)offset_high << 32 | offset_low, len,
				 advice);
}