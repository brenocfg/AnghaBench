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
typedef  int x ;
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static inline u8 flip_8_bits(u8 x)
{
	return (((x) & 0x01) << 3) | (((x) & 0x02) << 1)
	    | (((x) & 0x04) >> 1) | (((x) & 0x08) >> 3)
	    | (((x) & 0x10) << 3) | (((x) & 0x20) << 1)
	    | (((x) & 0x40) >> 1) | (((x) & 0x80) >> 3);
}