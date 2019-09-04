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
struct dax_device {struct inode inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_init_once (struct inode*) ; 
 int /*<<< orphan*/  memset (struct dax_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_once(void *_dax_dev)
{
	struct dax_device *dax_dev = _dax_dev;
	struct inode *inode = &dax_dev->inode;

	memset(dax_dev, 0, sizeof(*dax_dev));
	inode_init_once(inode);
}