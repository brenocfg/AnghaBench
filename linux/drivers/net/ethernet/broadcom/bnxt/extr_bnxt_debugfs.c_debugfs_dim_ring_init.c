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
struct dim {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct dim*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_dim_fops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void debugfs_dim_ring_init(struct dim *dim, int ring_idx,
				  struct dentry *dd)
{
	static char qname[16];

	snprintf(qname, 10, "%d", ring_idx);
	debugfs_create_file(qname, 0600, dd, dim, &debugfs_dim_fops);
}