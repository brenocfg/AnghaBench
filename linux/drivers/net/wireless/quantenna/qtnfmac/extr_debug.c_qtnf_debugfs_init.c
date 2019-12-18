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
struct qtnf_bus {int /*<<< orphan*/  dbg_dir; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (char const*,struct dentry*) ; 
 struct dentry* qtnf_get_debugfs_dir () ; 

void qtnf_debugfs_init(struct qtnf_bus *bus, const char *name)
{
	struct dentry *parent = qtnf_get_debugfs_dir();

	bus->dbg_dir = debugfs_create_dir(name, parent);
}