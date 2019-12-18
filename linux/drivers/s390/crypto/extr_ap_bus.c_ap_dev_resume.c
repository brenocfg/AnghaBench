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
struct device {int dummy; } ;
struct ap_device {TYPE_1__* drv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (struct ap_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ap_device*) ; 
 struct ap_device* to_ap_dev (struct device*) ; 

__attribute__((used)) static int ap_dev_resume(struct device *dev)
{
	struct ap_device *ap_dev = to_ap_dev(dev);

	if (ap_dev->drv && ap_dev->drv->resume)
		ap_dev->drv->resume(ap_dev);
	return 0;
}