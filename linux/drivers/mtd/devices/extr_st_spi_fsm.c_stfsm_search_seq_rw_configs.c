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
struct stfsm {TYPE_1__* info; } ;
struct seq_rw_config {scalar_t__ cmd; int flags; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */

__attribute__((used)) static struct seq_rw_config *
stfsm_search_seq_rw_configs(struct stfsm *fsm,
			    struct seq_rw_config cfgs[])
{
	struct seq_rw_config *config;
	int flags = fsm->info->flags;

	for (config = cfgs; config->cmd != 0; config++)
		if ((config->flags & flags) == config->flags)
			return config;

	return NULL;
}