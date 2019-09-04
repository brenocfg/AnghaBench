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
struct blk_cmd_filter {int /*<<< orphan*/  write_ok; int /*<<< orphan*/  read_ok; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EPERM ; 
 int FMODE_WRITE ; 
 struct blk_cmd_filter blk_default_cmd_filter ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (unsigned char,int /*<<< orphan*/ ) ; 

int blk_verify_command(unsigned char *cmd, fmode_t mode)
{
	struct blk_cmd_filter *filter = &blk_default_cmd_filter;

	/* root can do any command. */
	if (capable(CAP_SYS_RAWIO))
		return 0;

	/* Anybody who can open the device can do a read-safe command */
	if (test_bit(cmd[0], filter->read_ok))
		return 0;

	/* Write-safe commands require a writable open */
	if (test_bit(cmd[0], filter->write_ok) && (mode & FMODE_WRITE))
		return 0;

	return -EPERM;
}