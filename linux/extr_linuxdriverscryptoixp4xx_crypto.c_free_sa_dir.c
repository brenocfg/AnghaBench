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
struct ix_sa_dir {int /*<<< orphan*/  npe_ctx_phys; int /*<<< orphan*/  npe_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPE_CTX_LEN ; 
 int /*<<< orphan*/  ctx_pool ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_sa_dir(struct ix_sa_dir *dir)
{
	memset(dir->npe_ctx, 0, NPE_CTX_LEN);
	dma_pool_free(ctx_pool, dir->npe_ctx, dir->npe_ctx_phys);
}