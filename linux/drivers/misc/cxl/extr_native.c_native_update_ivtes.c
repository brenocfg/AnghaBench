#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cxl_context {TYPE_2__* afu; } ;
struct TYPE_8__ {TYPE_3__* sl_ops; } ;
struct TYPE_7__ {void (* update_dedicated_ivtes ) (struct cxl_context*) ;} ;
struct TYPE_6__ {scalar_t__ current_mode; TYPE_1__* adapter; } ;
struct TYPE_5__ {TYPE_4__* native; } ;

/* Variables and functions */
 scalar_t__ CXL_MODE_DEDICATED ; 
 scalar_t__ CXL_MODE_DIRECTED ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 void stub1 (struct cxl_context*) ; 
 void update_ivtes_directed (struct cxl_context*) ; 

__attribute__((used)) static void native_update_ivtes(struct cxl_context *ctx)
{
	if (ctx->afu->current_mode == CXL_MODE_DIRECTED)
		return update_ivtes_directed(ctx);
	if ((ctx->afu->current_mode == CXL_MODE_DEDICATED) &&
	    (ctx->afu->adapter->native->sl_ops->update_dedicated_ivtes))
		return ctx->afu->adapter->native->sl_ops->update_dedicated_ivtes(ctx);
	WARN(1, "native_update_ivtes: Bad mode\n");
}