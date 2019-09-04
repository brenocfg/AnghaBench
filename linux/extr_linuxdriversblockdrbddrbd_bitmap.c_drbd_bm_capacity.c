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
struct drbd_device {TYPE_1__* bitmap; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  bm_dev_capacity; } ;

/* Variables and functions */
 int /*<<< orphan*/  expect (TYPE_1__*) ; 

sector_t drbd_bm_capacity(struct drbd_device *device)
{
	if (!expect(device->bitmap))
		return 0;
	return device->bitmap->bm_dev_capacity;
}