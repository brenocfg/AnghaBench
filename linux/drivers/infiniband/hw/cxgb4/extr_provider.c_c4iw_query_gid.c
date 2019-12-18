#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union ib_gid {int /*<<< orphan*/ * raw; } ;
typedef  int u8 ;
struct ib_device {int dummy; } ;
struct TYPE_5__ {TYPE_1__** ports; } ;
struct TYPE_6__ {TYPE_2__ lldi; } ;
struct c4iw_dev {TYPE_3__ rdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,struct ib_device*,int,int,union ib_gid*) ; 
 struct c4iw_dev* to_c4iw_dev (struct ib_device*) ; 

__attribute__((used)) static int c4iw_query_gid(struct ib_device *ibdev, u8 port, int index,
			  union ib_gid *gid)
{
	struct c4iw_dev *dev;

	pr_debug("ibdev %p, port %d, index %d, gid %p\n",
		 ibdev, port, index, gid);
	if (!port)
		return -EINVAL;
	dev = to_c4iw_dev(ibdev);
	memset(&(gid->raw[0]), 0, sizeof(gid->raw));
	memcpy(&(gid->raw[0]), dev->rdev.lldi.ports[port-1]->dev_addr, 6);
	return 0;
}