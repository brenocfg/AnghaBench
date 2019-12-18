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
struct niu_parent {scalar_t__ plat_type; } ;
struct niu {int flags; struct niu_parent* parent; } ;

/* Variables and functions */
 int NIU_FLAGS_HOTPLUG_PHY ; 
 scalar_t__ PLAT_TYPE_NIU ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  niu_link_status (struct niu*,int*) ; 
 int niu_serdes_init (struct niu*) ; 
 int niu_xcvr_init (struct niu*) ; 

__attribute__((used)) static int niu_init_link(struct niu *np)
{
	struct niu_parent *parent = np->parent;
	int err, ignore;

	if (parent->plat_type == PLAT_TYPE_NIU) {
		err = niu_xcvr_init(np);
		if (err)
			return err;
		msleep(200);
	}
	err = niu_serdes_init(np);
	if (err && !(np->flags & NIU_FLAGS_HOTPLUG_PHY))
		return err;
	msleep(200);
	err = niu_xcvr_init(np);
	if (!err || (np->flags & NIU_FLAGS_HOTPLUG_PHY))
		niu_link_status(np, &ignore);
	return 0;
}