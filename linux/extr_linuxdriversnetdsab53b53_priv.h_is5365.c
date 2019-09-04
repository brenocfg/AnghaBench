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
struct b53_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int is5365(struct b53_device *dev)
{
#ifdef CONFIG_BCM47XX
	return dev->chip_id == BCM5365_DEVICE_ID;
#else
	return 0;
#endif
}