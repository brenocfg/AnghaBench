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
struct inode {int dummy; } ;
struct ibmasmfs_heartbeat_data {int dummy; } ;
struct file {struct ibmasmfs_heartbeat_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ibmasmfs_heartbeat_data*) ; 

__attribute__((used)) static int r_heartbeat_file_close(struct inode *inode, struct file *file)
{
	struct ibmasmfs_heartbeat_data *rhbeat = file->private_data;

	kfree(rhbeat);
	return 0;
}