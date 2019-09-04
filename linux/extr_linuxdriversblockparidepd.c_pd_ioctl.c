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
struct pd_unit {int access; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct pd_unit* private_data; } ;

/* Variables and functions */
#define  CDROMEJECT 128 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pd_eject ; 
 int /*<<< orphan*/  pd_mutex ; 
 int /*<<< orphan*/  pd_special_command (struct pd_unit*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pd_ioctl(struct block_device *bdev, fmode_t mode,
	 unsigned int cmd, unsigned long arg)
{
	struct pd_unit *disk = bdev->bd_disk->private_data;

	switch (cmd) {
	case CDROMEJECT:
		mutex_lock(&pd_mutex);
		if (disk->access == 1)
			pd_special_command(disk, pd_eject);
		mutex_unlock(&pd_mutex);
		return 0;
	default:
		return -EINVAL;
	}
}