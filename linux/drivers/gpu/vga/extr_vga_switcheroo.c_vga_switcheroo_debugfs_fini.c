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
struct vgasr_priv {int /*<<< orphan*/ * debugfs_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vga_switcheroo_debugfs_fini(struct vgasr_priv *priv)
{
	debugfs_remove_recursive(priv->debugfs_root);
	priv->debugfs_root = NULL;
}