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
struct dasd_eckd_private {scalar_t__ conf_len; int /*<<< orphan*/ * conf_data; } ;
struct dasd_device {TYPE_1__* path; struct dasd_eckd_private* private; } ;
struct TYPE_2__ {scalar_t__ chpid; scalar_t__ ssid; scalar_t__ cssid; int /*<<< orphan*/ * conf_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dasd_eckd_clear_conf_data(struct dasd_device *device)
{
	struct dasd_eckd_private *private = device->private;
	int i;

	private->conf_data = NULL;
	private->conf_len = 0;
	for (i = 0; i < 8; i++) {
		kfree(device->path[i].conf_data);
		device->path[i].conf_data = NULL;
		device->path[i].cssid = 0;
		device->path[i].ssid = 0;
		device->path[i].chpid = 0;
	}
}