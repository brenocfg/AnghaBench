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
struct dasd_cuir_message {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long dasd_eckd_cuir_scope (struct dasd_device*,int /*<<< orphan*/ ,struct dasd_cuir_message*) ; 
 int /*<<< orphan*/  dasd_path_add_cuirpm (struct dasd_device*,unsigned long) ; 
 unsigned long dasd_path_get_opm (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_path_remove_opm (struct dasd_device*,unsigned long) ; 

__attribute__((used)) static int dasd_eckd_cuir_remove_path(struct dasd_device *device, __u8 lpum,
				      struct dasd_cuir_message *cuir)
{
	unsigned long tbcpm;

	tbcpm = dasd_eckd_cuir_scope(device, lpum, cuir);
	/* nothing to do if path is not in use */
	if (!(dasd_path_get_opm(device) & tbcpm))
		return 0;
	if (!(dasd_path_get_opm(device) & ~tbcpm)) {
		/* no path would be left if the CUIR action is taken
		   return error */
		return -EINVAL;
	}
	/* remove device from operational path mask */
	dasd_path_remove_opm(device, tbcpm);
	dasd_path_add_cuirpm(device, tbcpm);
	return tbcpm;
}