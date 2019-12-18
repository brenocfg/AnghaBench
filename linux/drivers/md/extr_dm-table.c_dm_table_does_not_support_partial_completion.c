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
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_no_partial_completion ; 
 int dm_table_all_devices_attribute (struct dm_table*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool dm_table_does_not_support_partial_completion(struct dm_table *t)
{
	return dm_table_all_devices_attribute(t, device_no_partial_completion);
}