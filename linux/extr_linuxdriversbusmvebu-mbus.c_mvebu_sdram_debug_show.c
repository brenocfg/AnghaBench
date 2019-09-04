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
struct seq_file {int dummy; } ;
struct mvebu_mbus_state {TYPE_1__* soc; } ;
struct TYPE_2__ {int (* show_cpu_target ) (struct mvebu_mbus_state*,struct seq_file*,void*) ;} ;

/* Variables and functions */
 struct mvebu_mbus_state mbus_state ; 
 int stub1 (struct mvebu_mbus_state*,struct seq_file*,void*) ; 

__attribute__((used)) static int mvebu_sdram_debug_show(struct seq_file *seq, void *v)
{
	struct mvebu_mbus_state *mbus = &mbus_state;
	return mbus->soc->show_cpu_target(mbus, seq, v);
}