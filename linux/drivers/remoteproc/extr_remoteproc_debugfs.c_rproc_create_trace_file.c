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
struct rproc_debug_trace {int dummy; } ;
struct rproc {int /*<<< orphan*/  dev; int /*<<< orphan*/  dbg_dir; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_file (char const*,int,int /*<<< orphan*/ ,struct rproc_debug_trace*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  trace_rproc_ops ; 

struct dentry *rproc_create_trace_file(const char *name, struct rproc *rproc,
				       struct rproc_debug_trace *trace)
{
	struct dentry *tfile;

	tfile = debugfs_create_file(name, 0400, rproc->dbg_dir, trace,
				    &trace_rproc_ops);
	if (!tfile) {
		dev_err(&rproc->dev, "failed to create debugfs trace entry\n");
		return NULL;
	}

	return tfile;
}