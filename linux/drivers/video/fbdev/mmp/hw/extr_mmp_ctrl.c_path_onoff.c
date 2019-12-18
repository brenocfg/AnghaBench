#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmp_path {int status; TYPE_1__* panel; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_onoff ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_enabledisable (struct mmp_path*,int) ; 
 int /*<<< orphan*/  stat_name (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int) ; 

__attribute__((used)) static void path_onoff(struct mmp_path *path, int on)
{
	if (path->status == on) {
		dev_info(path->dev, "path %s is already %s\n",
				path->name, stat_name(path->status));
		return;
	}

	if (on) {
		path_enabledisable(path, 1);

		if (path->panel && path->panel->set_onoff)
			path->panel->set_onoff(path->panel, 1);
	} else {
		if (path->panel && path->panel->set_onoff)
			path->panel->set_onoff(path->panel, 0);

		path_enabledisable(path, 0);
	}
	path->status = on;
}