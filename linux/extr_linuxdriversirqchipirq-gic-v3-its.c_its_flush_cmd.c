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
struct its_node {int flags; } ;
struct its_cmd_block {int dummy; } ;

/* Variables and functions */
 int ITS_FLAGS_CMDQ_NEEDS_FLUSHING ; 
 int /*<<< orphan*/  dsb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_flush_dcache_to_poc (struct its_cmd_block*,int) ; 
 int /*<<< orphan*/  ishst ; 

__attribute__((used)) static void its_flush_cmd(struct its_node *its, struct its_cmd_block *cmd)
{
	/*
	 * Make sure the commands written to memory are observable by
	 * the ITS.
	 */
	if (its->flags & ITS_FLAGS_CMDQ_NEEDS_FLUSHING)
		gic_flush_dcache_to_poc(cmd, sizeof(*cmd));
	else
		dsb(ishst);
}