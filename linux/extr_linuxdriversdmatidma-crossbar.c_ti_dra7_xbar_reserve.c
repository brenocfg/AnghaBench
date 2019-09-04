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
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 

__attribute__((used)) static inline void ti_dra7_xbar_reserve(int offset, int len, unsigned long *p)
{
	for (; len > 0; len--)
		set_bit(offset + (len - 1), p);
}