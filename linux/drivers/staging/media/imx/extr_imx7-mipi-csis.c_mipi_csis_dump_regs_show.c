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
struct seq_file {struct csi_state* private; } ;
struct csi_state {int dummy; } ;

/* Variables and functions */
 int mipi_csis_dump_regs (struct csi_state*) ; 

__attribute__((used)) static int mipi_csis_dump_regs_show(struct seq_file *m, void *private)
{
	struct csi_state *state = m->private;

	return mipi_csis_dump_regs(state);
}