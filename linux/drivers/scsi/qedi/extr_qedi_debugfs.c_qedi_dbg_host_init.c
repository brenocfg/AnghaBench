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
struct qedi_debugfs_ops {int /*<<< orphan*/  name; } ;
struct qedi_dbg_ctx {int host_no; int /*<<< orphan*/  bdf_dentry; } ;
struct file_operations {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct qedi_dbg_ctx*,struct file_operations const*) ; 
 int /*<<< orphan*/  qedi_dbg_root ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void
qedi_dbg_host_init(struct qedi_dbg_ctx *qedi,
		   const struct qedi_debugfs_ops *dops,
		   const struct file_operations *fops)
{
	char host_dirname[32];

	sprintf(host_dirname, "host%u", qedi->host_no);
	qedi->bdf_dentry = debugfs_create_dir(host_dirname, qedi_dbg_root);

	while (dops) {
		if (!(dops->name))
			break;

		debugfs_create_file(dops->name, 0600, qedi->bdf_dentry, qedi,
				    fops);
		dops++;
		fops++;
	}
}