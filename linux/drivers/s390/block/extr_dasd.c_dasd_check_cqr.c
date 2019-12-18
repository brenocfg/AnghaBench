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
struct dasd_device {TYPE_1__* discipline; } ;
struct dasd_ccw_req {int /*<<< orphan*/  magic; struct dasd_device* startdev; } ;
struct TYPE_2__ {scalar_t__ name; int /*<<< orphan*/  ebcname; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 int EINVAL ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int dasd_check_cqr(struct dasd_ccw_req *cqr)
{
	struct dasd_device *device;

	if (cqr == NULL)
		return -EINVAL;
	device = cqr->startdev;
	if (strncmp((char *) &cqr->magic, device->discipline->ebcname, 4)) {
		DBF_DEV_EVENT(DBF_WARNING, device,
			    " dasd_ccw_req 0x%08x magic doesn't match"
			    " discipline 0x%08x",
			    cqr->magic,
			    *(unsigned int *) device->discipline->name);
		return -EINVAL;
	}
	return 0;
}