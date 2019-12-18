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
union ib_gid {int /*<<< orphan*/  raw; } ;
typedef  int /*<<< orphan*/  u8 ;
struct ib_device {int dummy; } ;
struct efa_dev {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct efa_dev* to_edev (struct ib_device*) ; 

int efa_query_gid(struct ib_device *ibdev, u8 port, int index,
		  union ib_gid *gid)
{
	struct efa_dev *dev = to_edev(ibdev);

	memcpy(gid->raw, dev->addr, sizeof(dev->addr));

	return 0;
}