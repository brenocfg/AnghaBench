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
struct tegra_bpmp {int /*<<< orphan*/ * debugfs_mirror; } ;
struct seqbuf {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int bpmp_populate_dir (struct tegra_bpmp*,struct seqbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seqbuf_init (struct seqbuf*,void*,size_t) ; 

__attribute__((used)) static int create_debugfs_mirror(struct tegra_bpmp *bpmp, void *buf,
				 size_t bufsize, struct dentry *root)
{
	struct seqbuf seqbuf;
	int err;

	bpmp->debugfs_mirror = debugfs_create_dir("debug", root);
	if (!bpmp->debugfs_mirror)
		return -ENOMEM;

	seqbuf_init(&seqbuf, buf, bufsize);
	err = bpmp_populate_dir(bpmp, &seqbuf, bpmp->debugfs_mirror, 0);
	if (err < 0) {
		debugfs_remove_recursive(bpmp->debugfs_mirror);
		bpmp->debugfs_mirror = NULL;
	}

	return err;
}