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
typedef  unsigned int const u8 ;
typedef  unsigned int u32 ;

/* Variables and functions */

__attribute__((used)) static inline u8
byte(const u32 x, const unsigned n)
{
	return x >> (n << 3);
}