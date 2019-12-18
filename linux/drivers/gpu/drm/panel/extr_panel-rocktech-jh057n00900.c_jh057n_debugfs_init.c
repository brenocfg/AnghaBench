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
struct jh057n {int /*<<< orphan*/  debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  allpixelson_fops ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct jh057n*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jh057n_debugfs_init(struct jh057n *ctx)
{
	ctx->debugfs = debugfs_create_dir(DRV_NAME, NULL);

	debugfs_create_file("allpixelson", 0600, ctx->debugfs, ctx,
			    &allpixelson_fops);
}