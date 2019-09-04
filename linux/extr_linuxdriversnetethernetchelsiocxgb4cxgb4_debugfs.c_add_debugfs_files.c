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
struct t4_debugfs_entry {int data; int /*<<< orphan*/  ops; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;
struct adapter {int /*<<< orphan*/  debugfs_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

void add_debugfs_files(struct adapter *adap,
		       struct t4_debugfs_entry *files,
		       unsigned int nfiles)
{
	int i;

	/* debugfs support is best effort */
	for (i = 0; i < nfiles; i++)
		debugfs_create_file(files[i].name, files[i].mode,
				    adap->debugfs_root,
				    (void *)adap + files[i].data,
				    files[i].ops);
}