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
typedef  int /*<<< orphan*/  u8 ;
struct ifla_vf_stats {int dummy; } ;
struct TYPE_2__ {int (* get_vf_stats ) (struct ib_device*,int,int /*<<< orphan*/ ,struct ifla_vf_stats*) ;} ;
struct ib_device {TYPE_1__ ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct ib_device*,int,int /*<<< orphan*/ ,struct ifla_vf_stats*) ; 

int ib_get_vf_stats(struct ib_device *device, int vf, u8 port,
		    struct ifla_vf_stats *stats)
{
	if (!device->ops.get_vf_stats)
		return -EOPNOTSUPP;

	return device->ops.get_vf_stats(device, vf, port, stats);
}