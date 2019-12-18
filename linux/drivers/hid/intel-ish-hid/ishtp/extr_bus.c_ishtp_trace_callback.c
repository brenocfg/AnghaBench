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
struct ishtp_cl_device {TYPE_1__* ishtp_dev; } ;
struct TYPE_2__ {void* print_log; } ;

/* Variables and functions */

void *ishtp_trace_callback(struct ishtp_cl_device *cl_device)
{
	return cl_device->ishtp_dev->print_log;
}