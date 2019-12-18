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
struct kfd_dbgdev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbgdev_address_watch_disable_nodiq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dbgdev_unregister_nodiq(struct kfd_dbgdev *dbgdev)
{
	/* disable watch address */
	dbgdev_address_watch_disable_nodiq(dbgdev->dev);
	return 0;
}