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
struct cxl_context {scalar_t__ mapping; scalar_t__ kernelapi; } ;

/* Variables and functions */
 int /*<<< orphan*/  cxl_fs_cnt ; 
 int /*<<< orphan*/  cxl_vfs_mount ; 
 int /*<<< orphan*/  simple_release_fs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void cxl_release_mapping(struct cxl_context *ctx)
{
	if (ctx->kernelapi && ctx->mapping)
		simple_release_fs(&cxl_vfs_mount, &cxl_fs_cnt);
}