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
struct can_rx_offload {scalar_t__ inc; } ;

/* Variables and functions */

__attribute__((used)) static inline bool can_rx_offload_le(struct can_rx_offload *offload, unsigned int a, unsigned int b)
{
	if (offload->inc)
		return a <= b;
	else
		return a >= b;
}