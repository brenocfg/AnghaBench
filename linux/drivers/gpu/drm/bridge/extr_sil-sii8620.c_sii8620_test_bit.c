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
typedef  unsigned int u8 ;

/* Variables and functions */
 unsigned int BITS_PER_BYTE ; 

__attribute__((used)) static bool sii8620_test_bit(unsigned int nr, const u8 *addr)
{
	return 1 & (addr[nr / BITS_PER_BYTE] >> (nr % BITS_PER_BYTE));
}