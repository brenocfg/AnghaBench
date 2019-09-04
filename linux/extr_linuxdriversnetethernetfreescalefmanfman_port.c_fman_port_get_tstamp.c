#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ time_stamp_offset; } ;
struct fman_port {TYPE_1__ buffer_offsets; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ILLEGAL_BASE ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 

int fman_port_get_tstamp(struct fman_port *port, const void *data, u64 *tstamp)
{
	if (port->buffer_offsets.time_stamp_offset == ILLEGAL_BASE)
		return -EINVAL;

	*tstamp = be64_to_cpu(*(__be64 *)(data +
			port->buffer_offsets.time_stamp_offset));

	return 0;
}