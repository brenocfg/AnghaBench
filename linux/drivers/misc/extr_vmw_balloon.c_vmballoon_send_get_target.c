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
typedef  unsigned long u32 ;
struct vmballoon {int capabilities; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int VMW_BALLOON_64_BIT_TARGET ; 
 int /*<<< orphan*/  VMW_BALLOON_CMD_GET_TARGET ; 
 unsigned long VMW_BALLOON_SUCCESS ; 
 unsigned long totalram_pages () ; 
 unsigned long vmballoon_cmd (struct vmballoon*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmballoon_send_get_target(struct vmballoon *b)
{
	unsigned long status;
	unsigned long limit;

	limit = totalram_pages();

	/* Ensure limit fits in 32-bits if 64-bit targets are not supported */
	if (!(b->capabilities & VMW_BALLOON_64_BIT_TARGET) &&
	    limit != (u32)limit)
		return -EINVAL;

	status = vmballoon_cmd(b, VMW_BALLOON_CMD_GET_TARGET, limit, 0);

	return status == VMW_BALLOON_SUCCESS ? 0 : -EIO;
}