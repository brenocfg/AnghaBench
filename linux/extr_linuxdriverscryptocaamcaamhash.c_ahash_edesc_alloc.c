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
typedef  int /*<<< orphan*/  u32 ;
struct sec4_sg_entry {int dummy; } ;
struct caam_hash_ctx {int /*<<< orphan*/  jrdev; } ;
struct ahash_edesc {int /*<<< orphan*/  hw_desc; } ;
typedef  int gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int GFP_DMA ; 
 int HDR_REVERSE ; 
 int HDR_SHARE_DEFER ; 
 int /*<<< orphan*/  desc_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_job_desc_shared (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ahash_edesc* kzalloc (int,int) ; 

__attribute__((used)) static struct ahash_edesc *ahash_edesc_alloc(struct caam_hash_ctx *ctx,
					     int sg_num, u32 *sh_desc,
					     dma_addr_t sh_desc_dma,
					     gfp_t flags)
{
	struct ahash_edesc *edesc;
	unsigned int sg_size = sg_num * sizeof(struct sec4_sg_entry);

	edesc = kzalloc(sizeof(*edesc) + sg_size, GFP_DMA | flags);
	if (!edesc) {
		dev_err(ctx->jrdev, "could not allocate extended descriptor\n");
		return NULL;
	}

	init_job_desc_shared(edesc->hw_desc, sh_desc_dma, desc_len(sh_desc),
			     HDR_SHARE_DEFER | HDR_REVERSE);

	return edesc;
}