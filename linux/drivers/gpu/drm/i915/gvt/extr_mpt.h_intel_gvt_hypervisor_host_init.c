#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mpt; } ;
struct TYPE_3__ {int (* host_init ) (struct device*,void*,void const*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_2__ intel_gvt_host ; 
 int stub1 (struct device*,void*,void const*) ; 

__attribute__((used)) static inline int intel_gvt_hypervisor_host_init(struct device *dev,
						 void *gvt, const void *ops)
{
	if (!intel_gvt_host.mpt->host_init)
		return -ENODEV;

	return intel_gvt_host.mpt->host_init(dev, gvt, ops);
}