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
struct gb_host_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  svc; } ;

/* Variables and functions */
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int gb_svc_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_gb_hd_add (struct gb_host_device*) ; 

int gb_hd_add(struct gb_host_device *hd)
{
	int ret;

	ret = device_add(&hd->dev);
	if (ret)
		return ret;

	ret = gb_svc_add(hd->svc);
	if (ret) {
		device_del(&hd->dev);
		return ret;
	}

	trace_gb_hd_add(hd);

	return 0;
}