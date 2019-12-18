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
struct vmballoon {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  VMW_BALLOON_CMD_GUEST_ID ; 
 int /*<<< orphan*/  VMW_BALLOON_GUEST_ID ; 
 unsigned long VMW_BALLOON_SUCCESS ; 
 unsigned long vmballoon_cmd (struct vmballoon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmballoon_send_guest_id(struct vmballoon *b)
{
	unsigned long status;

	status = vmballoon_cmd(b, VMW_BALLOON_CMD_GUEST_ID,
			       VMW_BALLOON_GUEST_ID, 0);

	return status == VMW_BALLOON_SUCCESS ? 0 : -EIO;
}