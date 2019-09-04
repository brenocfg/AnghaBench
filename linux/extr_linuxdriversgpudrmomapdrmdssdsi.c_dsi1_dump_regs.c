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
struct seq_file {int dummy; } ;
struct dsi_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsi_dump_dsi_regs (struct dsi_data*,struct seq_file*) ; 
 struct dsi_data* dsi_get_dsi_from_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dsi1_dump_regs(struct seq_file *s, void *p)
{
	struct dsi_data *dsi = dsi_get_dsi_from_id(0);

	dsi_dump_dsi_regs(dsi, s);
	return 0;
}