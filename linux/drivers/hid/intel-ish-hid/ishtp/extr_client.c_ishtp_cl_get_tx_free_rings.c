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
struct ishtp_cl {int tx_ring_free_size; } ;

/* Variables and functions */

int ishtp_cl_get_tx_free_rings(struct ishtp_cl *cl)
{
	return cl->tx_ring_free_size;
}