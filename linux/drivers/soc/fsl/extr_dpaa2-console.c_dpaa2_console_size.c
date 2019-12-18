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
struct console_data {scalar_t__ cur_ptr; scalar_t__ end_of_data; scalar_t__ end_addr; scalar_t__ start_addr; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */

__attribute__((used)) static ssize_t dpaa2_console_size(struct console_data *cd)
{
	ssize_t size;

	if (cd->cur_ptr <= cd->end_of_data)
		size = cd->end_of_data - cd->cur_ptr;
	else
		size = (cd->end_addr - cd->cur_ptr) +
			(cd->end_of_data - cd->start_addr);

	return size;
}