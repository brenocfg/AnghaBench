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
struct ci_hdrc {int hw_ep_max; } ;

/* Variables and functions */

__attribute__((used)) static inline int ep_to_bit(struct ci_hdrc *ci, int n)
{
	int fill = 16 - ci->hw_ep_max / 2;

	if (n >= ci->hw_ep_max / 2)
		n += fill;

	return n;
}