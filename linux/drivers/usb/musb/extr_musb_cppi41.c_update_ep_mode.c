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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 update_ep_mode(unsigned ep, unsigned mode, u32 old)
{
	unsigned shift;

	shift = (ep - 1) * 2;
	old &= ~(3 << shift);
	old |= mode << shift;
	return old;
}