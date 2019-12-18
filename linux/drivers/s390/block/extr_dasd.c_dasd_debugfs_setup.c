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
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 struct dentry* debugfs_create_dir (char const*,struct dentry*) ; 

__attribute__((used)) static struct dentry *dasd_debugfs_setup(const char *name,
					 struct dentry *base_dentry)
{
	struct dentry *pde;

	if (!base_dentry)
		return NULL;
	pde = debugfs_create_dir(name, base_dentry);
	if (!pde || IS_ERR(pde))
		return NULL;
	return pde;
}