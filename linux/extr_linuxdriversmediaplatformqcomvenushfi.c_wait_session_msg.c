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
struct venus_inst {scalar_t__ error; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 scalar_t__ HFI_ERR_NONE ; 
 int /*<<< orphan*/  TIMEOUT ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_session_msg(struct venus_inst *inst)
{
	int ret;

	ret = wait_for_completion_timeout(&inst->done, TIMEOUT);
	if (!ret)
		return -ETIMEDOUT;

	if (inst->error != HFI_ERR_NONE)
		return -EIO;

	return 0;
}