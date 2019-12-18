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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int (* set_vf_guid ) (struct ib_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct ib_device {TYPE_1__ ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct ib_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ib_set_vf_guid(struct ib_device *device, int vf, u8 port, u64 guid,
		   int type)
{
	if (!device->ops.set_vf_guid)
		return -EOPNOTSUPP;

	return device->ops.set_vf_guid(device, vf, port, guid, type);
}