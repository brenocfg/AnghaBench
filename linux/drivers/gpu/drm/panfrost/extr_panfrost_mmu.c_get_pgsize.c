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

/* Variables and functions */
 int SZ_2M ; 
 size_t SZ_4K ; 

__attribute__((used)) static size_t get_pgsize(u64 addr, size_t size)
{
	if (addr & (SZ_2M - 1) || size < SZ_2M)
		return SZ_4K;

	return SZ_2M;
}