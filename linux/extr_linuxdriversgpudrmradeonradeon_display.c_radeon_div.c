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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int do_div (int,int) ; 

__attribute__((used)) static inline uint32_t radeon_div(uint64_t n, uint32_t d)
{
	uint64_t mod;

	n += d / 2;

	mod = do_div(n, d);
	return n;
}