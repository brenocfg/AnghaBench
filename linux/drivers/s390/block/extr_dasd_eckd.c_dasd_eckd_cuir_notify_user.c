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
struct dasd_device {TYPE_1__* path; } ;
struct TYPE_2__ {int /*<<< orphan*/  chpid; int /*<<< orphan*/  cssid; } ;

/* Variables and functions */
 int CUIR_QUIESCE ; 
 int CUIR_RESUME ; 
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 int ffs (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dasd_eckd_cuir_notify_user(struct dasd_device *device,
				       unsigned long paths, int action)
{
	int pos;

	while (paths) {
		/* get position of bit in mask */
		pos = 8 - ffs(paths);
		/* get channel path descriptor from this position */
		if (action == CUIR_QUIESCE)
			pr_warn("Service on the storage server caused path %x.%02x to go offline",
				device->path[pos].cssid,
				device->path[pos].chpid);
		else if (action == CUIR_RESUME)
			pr_info("Path %x.%02x is back online after service on the storage server",
				device->path[pos].cssid,
				device->path[pos].chpid);
		clear_bit(7 - pos, &paths);
	}
}