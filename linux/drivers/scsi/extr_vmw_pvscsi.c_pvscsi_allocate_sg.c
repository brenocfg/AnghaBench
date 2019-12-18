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
struct pvscsi_sg_list {int dummy; } ;
struct pvscsi_ctx {int /*<<< orphan*/ * sgl; scalar_t__ sglPA; } ;
struct pvscsi_adapter {int req_depth; struct pvscsi_ctx* cmd_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int SGL_SIZE ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int) ; 

__attribute__((used)) static int pvscsi_allocate_sg(struct pvscsi_adapter *adapter)
{
	struct pvscsi_ctx *ctx;
	int i;

	ctx = adapter->cmd_map;
	BUILD_BUG_ON(sizeof(struct pvscsi_sg_list) > SGL_SIZE);

	for (i = 0; i < adapter->req_depth; ++i, ++ctx) {
		ctx->sgl = (void *)__get_free_pages(GFP_KERNEL,
						    get_order(SGL_SIZE));
		ctx->sglPA = 0;
		BUG_ON(!IS_ALIGNED(((unsigned long)ctx->sgl), PAGE_SIZE));
		if (!ctx->sgl) {
			for (; i >= 0; --i, --ctx) {
				free_pages((unsigned long)ctx->sgl,
					   get_order(SGL_SIZE));
				ctx->sgl = NULL;
			}
			return -ENOMEM;
		}
	}

	return 0;
}