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
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 void const* of_device_get_match_data (struct device const*) ; 

__attribute__((used)) static const void *
of_fwnode_device_get_match_data(const struct fwnode_handle *fwnode,
				const struct device *dev)
{
	return of_device_get_match_data(dev);
}