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
struct vgasr_priv {int /*<<< orphan*/  switch_file; scalar_t__ debugfs_root; } ;

/* Variables and functions */
 scalar_t__ debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  vga_switcheroo_debugfs_fini (struct vgasr_priv*) ; 
 int /*<<< orphan*/  vga_switcheroo_debugfs_fops ; 

__attribute__((used)) static int vga_switcheroo_debugfs_init(struct vgasr_priv *priv)
{
	static const char mp[] = "/sys/kernel/debug";

	/* already initialised */
	if (priv->debugfs_root)
		return 0;
	priv->debugfs_root = debugfs_create_dir("vgaswitcheroo", NULL);

	if (!priv->debugfs_root) {
		pr_err("Cannot create %s/vgaswitcheroo\n", mp);
		goto fail;
	}

	priv->switch_file = debugfs_create_file("switch", 0644,
						priv->debugfs_root, NULL,
						&vga_switcheroo_debugfs_fops);
	if (!priv->switch_file) {
		pr_err("cannot create %s/vgaswitcheroo/switch\n", mp);
		goto fail;
	}
	return 0;
fail:
	vga_switcheroo_debugfs_fini(priv);
	return -1;
}