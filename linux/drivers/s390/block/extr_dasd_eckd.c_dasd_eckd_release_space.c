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
struct format_data_t {int intensity; int /*<<< orphan*/  stop_unit; int /*<<< orphan*/  start_unit; } ;
struct dasd_device {int dummy; } ;

/* Variables and functions */
 int DASD_FMT_INT_ESE_FULL ; 
 int EINVAL ; 
 int dasd_eckd_release_space_full (struct dasd_device*) ; 
 int dasd_eckd_release_space_trks (struct dasd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dasd_eckd_release_space(struct dasd_device *device,
				   struct format_data_t *rdata)
{
	if (rdata->intensity & DASD_FMT_INT_ESE_FULL)
		return dasd_eckd_release_space_full(device);
	else if (rdata->intensity == 0)
		return dasd_eckd_release_space_trks(device, rdata->start_unit,
						    rdata->stop_unit);
	else
		return -EINVAL;
}