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
struct dasd_uid {int dummy; } ;
struct dasd_eckd_private {int /*<<< orphan*/  uid; } ;
struct dasd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  create_uid (struct dasd_eckd_private*) ; 
 int /*<<< orphan*/  dasd_eckd_get_uid (struct dasd_device*,struct dasd_uid*) ; 
 int memcmp (struct dasd_uid*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dasd_eckd_compare_path_uid(struct dasd_device *device,
				      struct dasd_eckd_private *private)
{
	struct dasd_uid device_uid;

	create_uid(private);
	dasd_eckd_get_uid(device, &device_uid);

	return memcmp(&device_uid, &private->uid, sizeof(struct dasd_uid));
}