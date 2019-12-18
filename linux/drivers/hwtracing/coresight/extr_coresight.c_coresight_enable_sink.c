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
typedef  int /*<<< orphan*/  u32 ;
struct coresight_device {int enable; } ;
struct TYPE_2__ {int (* enable ) (struct coresight_device*,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* sink_ops (struct coresight_device*) ; 
 int stub1 (struct coresight_device*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int coresight_enable_sink(struct coresight_device *csdev,
				 u32 mode, void *data)
{
	int ret;

	/*
	 * We need to make sure the "new" session is compatible with the
	 * existing "mode" of operation.
	 */
	if (!sink_ops(csdev)->enable)
		return -EINVAL;

	ret = sink_ops(csdev)->enable(csdev, mode, data);
	if (ret)
		return ret;
	csdev->enable = true;

	return 0;
}