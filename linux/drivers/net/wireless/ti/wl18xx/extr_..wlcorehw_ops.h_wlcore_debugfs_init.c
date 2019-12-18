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
struct wl1271 {TYPE_1__* ops; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int (* debugfs_init ) (struct wl1271*,struct dentry*) ;} ;

/* Variables and functions */
 int stub1 (struct wl1271*,struct dentry*) ; 

__attribute__((used)) static inline int
wlcore_debugfs_init(struct wl1271 *wl, struct dentry *rootdir)
{
	if (wl->ops->debugfs_init)
		return wl->ops->debugfs_init(wl, rootdir);

	return 0;
}