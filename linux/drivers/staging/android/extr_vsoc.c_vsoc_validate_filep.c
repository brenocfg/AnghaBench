#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int /*<<< orphan*/  private_data; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBADFD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  iminor (int /*<<< orphan*/ ) ; 
 TYPE_2__ vsoc_dev ; 
 int vsoc_validate_inode (int /*<<< orphan*/ ) ; 

inline int vsoc_validate_filep(struct file *filp)
{
	int ret = vsoc_validate_inode(file_inode(filp));

	if (ret)
		return ret;
	if (!filp->private_data) {
		dev_err(&vsoc_dev.dev->dev,
			"No private data on fd, region %d\n",
			iminor(file_inode(filp)));
		return -EBADFD;
	}
	return 0;
}