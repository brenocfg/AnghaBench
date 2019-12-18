#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_2__ {scalar_t__* range; scalar_t__* offset; } ;
struct cxl_context {TYPE_1__ irqs; struct cxl_afu* afu; } ;
struct cxl_afu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_IVTE_Limit_An ; 
 int /*<<< orphan*/  CXL_PSL_IVTE_Offset_An ; 
 int /*<<< orphan*/  cxl_p1n_write (struct cxl_afu*,int /*<<< orphan*/ ,int) ; 

void cxl_update_dedicated_ivtes_psl8(struct cxl_context *ctx)
{
	struct cxl_afu *afu = ctx->afu;

	cxl_p1n_write(afu, CXL_PSL_IVTE_Offset_An,
		       (((u64)ctx->irqs.offset[0] & 0xffff) << 48) |
		       (((u64)ctx->irqs.offset[1] & 0xffff) << 32) |
		       (((u64)ctx->irqs.offset[2] & 0xffff) << 16) |
			((u64)ctx->irqs.offset[3] & 0xffff));
	cxl_p1n_write(afu, CXL_PSL_IVTE_Limit_An, (u64)
		       (((u64)ctx->irqs.range[0] & 0xffff) << 48) |
		       (((u64)ctx->irqs.range[1] & 0xffff) << 32) |
		       (((u64)ctx->irqs.range[2] & 0xffff) << 16) |
			((u64)ctx->irqs.range[3] & 0xffff));
}