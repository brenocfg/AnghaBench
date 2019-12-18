#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct file {struct cxl_context* private_data; } ;
struct cxl_context {scalar_t__ status; TYPE_1__* afu; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* link_ok ) (int /*<<< orphan*/ ,TYPE_1__*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ STARTED ; 
 int cxl_context_iomap (struct cxl_context*,struct vm_area_struct*) ; 
 TYPE_2__* cxl_ops ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*) ; 

int afu_mmap(struct file *file, struct vm_area_struct *vm)
{
	struct cxl_context *ctx = file->private_data;

	/* AFU must be started before we can MMIO */
	if (ctx->status != STARTED)
		return -EIO;

	if (!cxl_ops->link_ok(ctx->afu->adapter, ctx->afu))
		return -EIO;

	return cxl_context_iomap(ctx, vm);
}