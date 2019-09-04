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
struct fsi_msg {int msg; int bits; } ;

/* Variables and functions */

__attribute__((used)) static void msg_finish_cmd(struct fsi_msg *cmd)
{
	/* Left align message */
	cmd->msg <<= (64 - cmd->bits);
}