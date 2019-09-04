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
struct v4l2_encoder_cmd {int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void v4l_print_encoder_cmd(const void *arg, bool write_only)
{
	const struct v4l2_encoder_cmd *p = arg;

	pr_cont("cmd=%d, flags=0x%x\n",
			p->cmd, p->flags);
}