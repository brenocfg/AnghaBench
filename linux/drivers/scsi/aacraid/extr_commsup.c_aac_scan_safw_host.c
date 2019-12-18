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
struct aac_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aac_schedule_safw_scan_worker (struct aac_dev*) ; 
 int aac_update_safw_host_devices (struct aac_dev*) ; 

__attribute__((used)) static int aac_scan_safw_host(struct aac_dev *dev)
{
	int rcode = 0;

	rcode = aac_update_safw_host_devices(dev);
	if (rcode)
		aac_schedule_safw_scan_worker(dev);

	return rcode;
}