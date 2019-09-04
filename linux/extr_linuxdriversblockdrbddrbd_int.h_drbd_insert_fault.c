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
struct drbd_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int
drbd_insert_fault(struct drbd_device *device, unsigned int type) {
#ifdef CONFIG_DRBD_FAULT_INJECTION
	return drbd_fault_rate &&
		(drbd_enable_faults & (1<<type)) &&
		_drbd_insert_fault(device, type);
#else
	return 0;
#endif
}