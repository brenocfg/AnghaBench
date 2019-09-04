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
 int /*<<< orphan*/  D_NEGOTIATING ; 
 unsigned long _drbd_bm_total_weight (struct drbd_device*) ; 
 int /*<<< orphan*/  get_ldev_if_state (struct drbd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ldev (struct drbd_device*) ; 

unsigned long drbd_bm_total_weight(struct drbd_device *device)
{
	unsigned long s;
	/* if I don't have a disk, I don't know about out-of-sync status */
	if (!get_ldev_if_state(device, D_NEGOTIATING))
		return 0;
	s = _drbd_bm_total_weight(device);
	put_ldev(device);
	return s;
}