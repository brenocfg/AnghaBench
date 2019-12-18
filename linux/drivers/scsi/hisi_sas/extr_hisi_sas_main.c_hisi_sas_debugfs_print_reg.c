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
typedef  int /*<<< orphan*/  u32 ;
struct seq_file {int dummy; } ;
struct hisi_sas_debugfs_reg {int count; int /*<<< orphan*/  lu; int /*<<< orphan*/  base_off; } ;

/* Variables and functions */
 char* hisi_sas_debugfs_to_reg_name (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void hisi_sas_debugfs_print_reg(u32 *regs_val, const void *ptr,
				       struct seq_file *s)
{
	const struct hisi_sas_debugfs_reg *reg = ptr;
	int i;

	for (i = 0; i < reg->count; i++) {
		int off = i * 4;
		const char *name;

		name = hisi_sas_debugfs_to_reg_name(off, reg->base_off,
						    reg->lu);

		if (name)
			seq_printf(s, "0x%08x 0x%08x %s\n", off,
				   regs_val[i], name);
		else
			seq_printf(s, "0x%08x 0x%08x\n", off,
				   regs_val[i]);
	}
}