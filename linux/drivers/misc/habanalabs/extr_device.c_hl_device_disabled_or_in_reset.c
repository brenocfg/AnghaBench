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
struct hl_device {int /*<<< orphan*/  in_reset; scalar_t__ disabled; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

bool hl_device_disabled_or_in_reset(struct hl_device *hdev)
{
	if ((hdev->disabled) || (atomic_read(&hdev->in_reset)))
		return true;
	else
		return false;
}