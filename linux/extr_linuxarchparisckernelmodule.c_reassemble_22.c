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

__attribute__((used)) static inline int reassemble_22(int as22)
{
	return (((as22 & 0x200000) >> 21) |
		((as22 & 0x1f0000) << 5) |
		((as22 & 0x00f800) << 5) |
		((as22 & 0x000400) >> 8) |
		((as22 & 0x0003ff) << 3));
}