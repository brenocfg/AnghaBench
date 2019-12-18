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
struct sony_sc {int quirks; int device_id; } ;

/* Variables and functions */
 int DUALSHOCK4_CONTROLLER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SIXAXIS_CONTROLLER ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sony_device_id_allocator ; 

__attribute__((used)) static int sony_set_device_id(struct sony_sc *sc)
{
	int ret;

	/*
	 * Only DualShock 4 or Sixaxis controllers get an id.
	 * All others are set to -1.
	 */
	if ((sc->quirks & SIXAXIS_CONTROLLER) ||
	    (sc->quirks & DUALSHOCK4_CONTROLLER)) {
		ret = ida_simple_get(&sony_device_id_allocator, 0, 0,
					GFP_KERNEL);
		if (ret < 0) {
			sc->device_id = -1;
			return ret;
		}
		sc->device_id = ret;
	} else {
		sc->device_id = -1;
	}

	return 0;
}