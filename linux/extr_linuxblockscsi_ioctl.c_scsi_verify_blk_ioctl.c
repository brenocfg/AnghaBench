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
struct block_device {struct block_device* bd_contains; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int ENOIOCTLCMD ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 

int scsi_verify_blk_ioctl(struct block_device *bd, unsigned int cmd)
{
	if (bd && bd == bd->bd_contains)
		return 0;

	if (capable(CAP_SYS_RAWIO))
		return 0;

	return -ENOIOCTLCMD;
}