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
struct TYPE_2__ {scalar_t__ n_bitmap_hints; } ;

/* Variables and functions */

void drbd_bm_reset_al_hints(struct drbd_device *device)
{
	device->bitmap->n_bitmap_hints = 0;
}