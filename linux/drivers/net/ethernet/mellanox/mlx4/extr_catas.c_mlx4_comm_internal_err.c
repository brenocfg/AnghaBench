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
 scalar_t__ COMM_CHAN_EVENT_INTERNAL_ERR ; 

int mlx4_comm_internal_err(u32 slave_read)
{
	return (u32)COMM_CHAN_EVENT_INTERNAL_ERR ==
		(slave_read & (u32)COMM_CHAN_EVENT_INTERNAL_ERR) ? 1 : 0;
}