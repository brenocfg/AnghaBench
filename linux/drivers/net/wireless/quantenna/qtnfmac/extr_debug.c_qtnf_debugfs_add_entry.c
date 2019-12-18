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
struct qtnf_bus {int /*<<< orphan*/  dbg_dir; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_devm_seqfile (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int (*) (struct seq_file*,void*)) ; 

void qtnf_debugfs_add_entry(struct qtnf_bus *bus, const char *name,
			    int (*fn)(struct seq_file *seq, void *data))
{
	debugfs_create_devm_seqfile(bus->dev, name, bus->dbg_dir, fn);
}