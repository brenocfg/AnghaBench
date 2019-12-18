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
struct dwc3_ep {int /*<<< orphan*/  name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  dwc3_debugfs_create_endpoint_files (struct dwc3_ep*,struct dentry*) ; 

__attribute__((used)) static void dwc3_debugfs_create_endpoint_dir(struct dwc3_ep *dep,
		struct dentry *parent)
{
	struct dentry		*dir;

	dir = debugfs_create_dir(dep->name, parent);
	dwc3_debugfs_create_endpoint_files(dep, dir);
}