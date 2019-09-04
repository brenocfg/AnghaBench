#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct cxl_context {TYPE_2__* elem; TYPE_4__* afu; } ;
struct cxl {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* link_ok ) (struct cxl*,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {TYPE_3__* native; struct cxl* adapter; } ;
struct TYPE_8__ {int /*<<< orphan*/  spa_mutex; } ;
struct TYPE_6__ {int /*<<< orphan*/  pid; } ;
struct TYPE_7__ {int /*<<< orphan*/  lpid; TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL_LBISEL ; 
 int /*<<< orphan*/  CXL_PSL_SLBIA ; 
 int CXL_TLB_SLB_IQ_LPIDPID ; 
 int CXL_TLB_SLB_P ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_5__* cxl_ops ; 
 int cxl_p1_read (struct cxl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_p1_write (struct cxl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cxl*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void slb_invalid(struct cxl_context *ctx)
{
	struct cxl *adapter = ctx->afu->adapter;
	u64 slbia;

	WARN_ON(!mutex_is_locked(&ctx->afu->native->spa_mutex));

	cxl_p1_write(adapter, CXL_PSL_LBISEL,
			((u64)be32_to_cpu(ctx->elem->common.pid) << 32) |
			be32_to_cpu(ctx->elem->lpid));
	cxl_p1_write(adapter, CXL_PSL_SLBIA, CXL_TLB_SLB_IQ_LPIDPID);

	while (1) {
		if (!cxl_ops->link_ok(adapter, NULL))
			break;
		slbia = cxl_p1_read(adapter, CXL_PSL_SLBIA);
		if (!(slbia & CXL_TLB_SLB_P))
			break;
		cpu_relax();
	}
}