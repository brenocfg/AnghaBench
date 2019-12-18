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
typedef  int /*<<< orphan*/  u8 ;
struct lte_udev {int /*<<< orphan*/  gdm_ed; } ;

/* Variables and functions */

__attribute__((used)) static u8 gdm_usb_get_endian(void *priv_dev)
{
	struct lte_udev *udev = priv_dev;

	return udev->gdm_ed;
}