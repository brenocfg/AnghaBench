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
struct dasd_device {int dummy; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_generic_path_operational (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_path_add_opm (struct dasd_device*,scalar_t__) ; 
 int /*<<< orphan*/  dasd_path_get_opm (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_path_set_opm (struct dasd_device*,scalar_t__) ; 

int dasd_generic_verify_path(struct dasd_device *device, __u8 lpm)
{
	if (!dasd_path_get_opm(device) && lpm) {
		dasd_path_set_opm(device, lpm);
		dasd_generic_path_operational(device);
	} else
		dasd_path_add_opm(device, lpm);
	return 0;
}