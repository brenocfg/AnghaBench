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
struct nullb_cmd {int /*<<< orphan*/  tag; int /*<<< orphan*/  nq; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_cmd(struct nullb_cmd *cmd)
{
	put_tag(cmd->nq, cmd->tag);
}