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
struct cxl_context {struct cxl_afu* afu; } ;
struct cxl_afu {int dummy; } ;
struct TYPE_2__ {int (* afu_reset ) (struct cxl_afu*) ;int (* afu_check_and_enable ) (struct cxl_afu*) ;} ;

/* Variables and functions */
 TYPE_1__* cxl_ops ; 
 int stub1 (struct cxl_afu*) ; 
 int stub2 (struct cxl_afu*) ; 

int cxl_afu_reset(struct cxl_context *ctx)
{
	struct cxl_afu *afu = ctx->afu;
	int rc;

	rc = cxl_ops->afu_reset(afu);
	if (rc)
		return rc;

	return cxl_ops->afu_check_and_enable(afu);
}