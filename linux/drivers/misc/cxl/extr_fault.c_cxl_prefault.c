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
typedef  int /*<<< orphan*/  u64 ;
struct cxl_context {TYPE_1__* afu; } ;
struct TYPE_2__ {int prefault_mode; } ;

/* Variables and functions */
#define  CXL_PREFAULT_ALL 129 
#define  CXL_PREFAULT_WED 128 
 int /*<<< orphan*/  cxl_prefault_one (struct cxl_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_prefault_vma (struct cxl_context*) ; 

void cxl_prefault(struct cxl_context *ctx, u64 wed)
{
	switch (ctx->afu->prefault_mode) {
	case CXL_PREFAULT_WED:
		cxl_prefault_one(ctx, wed);
		break;
	case CXL_PREFAULT_ALL:
		cxl_prefault_vma(ctx);
		break;
	default:
		break;
	}
}