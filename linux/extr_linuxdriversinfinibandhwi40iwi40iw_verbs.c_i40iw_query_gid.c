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
union ib_gid {int /*<<< orphan*/  raw; } ;
typedef  int /*<<< orphan*/  u8 ;
struct ib_device {int dummy; } ;
struct i40iw_device {TYPE_1__* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct i40iw_device* to_iwdev (struct ib_device*) ; 

__attribute__((used)) static int i40iw_query_gid(struct ib_device *ibdev,
			   u8 port,
			   int index,
			   union ib_gid *gid)
{
	struct i40iw_device *iwdev = to_iwdev(ibdev);

	memset(gid->raw, 0, sizeof(gid->raw));
	ether_addr_copy(gid->raw, iwdev->netdev->dev_addr);
	return 0;
}