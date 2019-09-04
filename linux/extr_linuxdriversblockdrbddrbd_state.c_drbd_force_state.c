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
typedef  union drbd_state {int dummy; } drbd_state ;
struct drbd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_HARD ; 
 int /*<<< orphan*/  drbd_change_state (struct drbd_device*,int /*<<< orphan*/ ,union drbd_state,union drbd_state) ; 

void drbd_force_state(struct drbd_device *device,
	union drbd_state mask, union drbd_state val)
{
	drbd_change_state(device, CS_HARD, mask, val);
}