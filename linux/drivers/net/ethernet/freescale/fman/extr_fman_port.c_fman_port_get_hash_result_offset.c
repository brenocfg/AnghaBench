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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ hash_result_offset; } ;
struct fman_port {TYPE_1__ buffer_offsets; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ILLEGAL_BASE ; 

int fman_port_get_hash_result_offset(struct fman_port *port, u32 *offset)
{
	if (port->buffer_offsets.hash_result_offset == ILLEGAL_BASE)
		return -EINVAL;

	*offset = port->buffer_offsets.hash_result_offset;

	return 0;
}