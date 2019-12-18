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
struct ishtp_cl {int rx_ring_size; } ;

/* Variables and functions */

void ishtp_set_rx_ring_size(struct ishtp_cl *cl, int size)
{
	cl->rx_ring_size = size;
}