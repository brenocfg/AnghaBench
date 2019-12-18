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
struct slim_device {int /*<<< orphan*/  is_laddr_valid; } ;

/* Variables and functions */
 int slim_device_alloc_laddr (struct slim_device*,int) ; 

int slim_get_logical_addr(struct slim_device *sbdev)
{
	if (!sbdev->is_laddr_valid)
		return slim_device_alloc_laddr(sbdev, false);

	return 0;
}