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
struct vm_area_struct {int dummy; } ;
struct dvb_vb2_ctx {int /*<<< orphan*/  name; int /*<<< orphan*/  vb_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int) ; 
 int vb2_mmap (int /*<<< orphan*/ *,struct vm_area_struct*) ; 

int dvb_vb2_mmap(struct dvb_vb2_ctx *ctx, struct vm_area_struct *vma)
{
	int ret;

	ret = vb2_mmap(&ctx->vb_q, vma);
	if (ret) {
		dprintk(1, "[%s] errno=%d\n", ctx->name, ret);
		return ret;
	}
	dprintk(3, "[%s] ret=%d\n", ctx->name, ret);

	return 0;
}