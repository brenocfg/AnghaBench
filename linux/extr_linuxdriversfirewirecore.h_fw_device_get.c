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
struct fw_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct fw_device *fw_device_get(struct fw_device *device)
{
	get_device(&device->device);

	return device;
}