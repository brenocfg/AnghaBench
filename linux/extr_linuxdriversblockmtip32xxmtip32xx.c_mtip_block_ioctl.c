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
struct driver_data {int /*<<< orphan*/  dd_flag; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct driver_data* private_data; } ;

/* Variables and functions */
#define  BLKFLSBUF 128 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EACCES ; 
 int ENOTTY ; 
 int /*<<< orphan*/  MTIP_DDF_REMOVE_PENDING_BIT ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int mtip_hw_ioctl (struct driver_data*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtip_block_ioctl(struct block_device *dev,
			    fmode_t mode,
			    unsigned cmd,
			    unsigned long arg)
{
	struct driver_data *dd = dev->bd_disk->private_data;

	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

	if (!dd)
		return -ENOTTY;

	if (unlikely(test_bit(MTIP_DDF_REMOVE_PENDING_BIT, &dd->dd_flag)))
		return -ENOTTY;

	switch (cmd) {
	case BLKFLSBUF:
		return -ENOTTY;
	default:
		return mtip_hw_ioctl(dd, cmd, arg);
	}
}