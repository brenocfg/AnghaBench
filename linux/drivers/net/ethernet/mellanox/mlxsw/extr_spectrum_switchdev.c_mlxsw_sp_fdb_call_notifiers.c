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
typedef  int /*<<< orphan*/  u16 ;
struct switchdev_notifier_fdb_info {char const* addr; int offloaded; int /*<<< orphan*/  info; int /*<<< orphan*/  vid; } ;
struct net_device {int dummy; } ;
typedef  enum switchdev_notifier_type { ____Placeholder_switchdev_notifier_type } switchdev_notifier_type ;

/* Variables and functions */
 int /*<<< orphan*/  call_switchdev_notifiers (int,struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_fdb_call_notifiers(enum switchdev_notifier_type type,
			    const char *mac, u16 vid,
			    struct net_device *dev, bool offloaded)
{
	struct switchdev_notifier_fdb_info info;

	info.addr = mac;
	info.vid = vid;
	info.offloaded = offloaded;
	call_switchdev_notifiers(type, dev, &info.info, NULL);
}