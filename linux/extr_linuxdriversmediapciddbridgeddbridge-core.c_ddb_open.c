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
struct file {struct ddb* private_data; } ;
struct ddb {scalar_t__ ddb_dev_users; } ;

/* Variables and functions */
 int EBUSY ; 
 struct ddb** ddbs ; 
 size_t iminor (struct inode*) ; 

__attribute__((used)) static int ddb_open(struct inode *inode, struct file *file)
{
	struct ddb *dev = ddbs[iminor(inode)];

	if (dev->ddb_dev_users)
		return -EBUSY;
	dev->ddb_dev_users++;
	file->private_data = dev;
	return 0;
}