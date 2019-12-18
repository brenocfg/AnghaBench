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
struct vpbe_device {unsigned int current_out_index; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int vpbe_get_output(struct vpbe_device *vpbe_dev)
{
	return vpbe_dev->current_out_index;
}