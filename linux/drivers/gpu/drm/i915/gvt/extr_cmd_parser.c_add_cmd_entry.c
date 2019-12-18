#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_gvt {int /*<<< orphan*/  cmd_table; } ;
struct cmd_entry {TYPE_1__* info; int /*<<< orphan*/  hlist; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_cmd_entry(struct intel_gvt *gvt, struct cmd_entry *e)
{
	hash_add(gvt->cmd_table, &e->hlist, e->info->opcode);
}