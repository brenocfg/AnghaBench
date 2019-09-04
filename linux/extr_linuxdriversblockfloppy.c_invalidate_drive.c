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
struct block_device {TYPE_1__* bd_disk; } ;
struct TYPE_2__ {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_disk_change (struct block_device*) ; 
 int /*<<< orphan*/  fake_change ; 
 int /*<<< orphan*/  process_fd_request () ; 
 int /*<<< orphan*/  set_bit (long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int invalidate_drive(struct block_device *bdev)
{
	/* invalidate the buffer track to force a reread */
	set_bit((long)bdev->bd_disk->private_data, &fake_change);
	process_fd_request();
	check_disk_change(bdev);
	return 0;
}