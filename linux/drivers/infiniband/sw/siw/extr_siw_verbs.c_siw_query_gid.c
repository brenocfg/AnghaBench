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
union ib_gid {int /*<<< orphan*/ * raw; } ;
typedef  int /*<<< orphan*/  u8 ;
struct siw_device {TYPE_1__* netdev; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (union ib_gid*,int /*<<< orphan*/ ,int) ; 
 struct siw_device* to_siw_dev (struct ib_device*) ; 

int siw_query_gid(struct ib_device *base_dev, u8 port, int idx,
		  union ib_gid *gid)
{
	struct siw_device *sdev = to_siw_dev(base_dev);

	/* subnet_prefix == interface_id == 0; */
	memset(gid, 0, sizeof(*gid));
	memcpy(&gid->raw[0], sdev->netdev->dev_addr, 6);

	return 0;
}