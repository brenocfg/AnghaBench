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
typedef  int /*<<< orphan*/  u8 ;
struct update_gid_event_work {int /*<<< orphan*/  gid_attr; int /*<<< orphan*/  gid; int /*<<< orphan*/  gid_op; } ;
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 void update_gid (int /*<<< orphan*/ ,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void callback_for_addr_gid_device_scan(struct ib_device *device,
					      u8 port,
					      struct net_device *rdma_ndev,
					      void *cookie)
{
	struct update_gid_event_work *parsed = cookie;

	return update_gid(parsed->gid_op, device,
			  port, &parsed->gid,
			  &parsed->gid_attr);
}