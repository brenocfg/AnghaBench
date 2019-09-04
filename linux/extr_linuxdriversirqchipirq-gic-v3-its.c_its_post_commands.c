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
typedef  int /*<<< orphan*/  u64 ;
struct its_node {struct its_cmd_block* cmd_write; scalar_t__ base; } ;
struct its_cmd_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ GITS_CWRITER ; 
 int /*<<< orphan*/  its_cmd_ptr_to_offset (struct its_node*,struct its_cmd_block*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct its_cmd_block *its_post_commands(struct its_node *its)
{
	u64 wr = its_cmd_ptr_to_offset(its, its->cmd_write);

	writel_relaxed(wr, its->base + GITS_CWRITER);

	return its->cmd_write;
}