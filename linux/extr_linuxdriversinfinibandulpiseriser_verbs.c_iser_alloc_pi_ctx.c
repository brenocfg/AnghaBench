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
struct iser_pi_context {int /*<<< orphan*/  rsc; scalar_t__ sig_protected; scalar_t__ sig_mr_valid; int /*<<< orphan*/  sig_mr; } ;
struct iser_fr_desc {struct iser_pi_context* pi_ctx; } ;
struct iser_device {int dummy; } ;
struct ib_pd {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_MR_TYPE_SIGNATURE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_alloc_mr (struct ib_pd*,int /*<<< orphan*/ ,int) ; 
 int iser_alloc_reg_res (struct iser_device*,struct ib_pd*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  iser_err (char*) ; 
 int /*<<< orphan*/  iser_free_reg_res (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iser_pi_context*) ; 
 struct iser_pi_context* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iser_alloc_pi_ctx(struct iser_device *device,
		  struct ib_pd *pd,
		  struct iser_fr_desc *desc,
		  unsigned int size)
{
	struct iser_pi_context *pi_ctx = NULL;
	int ret;

	desc->pi_ctx = kzalloc(sizeof(*desc->pi_ctx), GFP_KERNEL);
	if (!desc->pi_ctx)
		return -ENOMEM;

	pi_ctx = desc->pi_ctx;

	ret = iser_alloc_reg_res(device, pd, &pi_ctx->rsc, size);
	if (ret) {
		iser_err("failed to allocate reg_resources\n");
		goto alloc_reg_res_err;
	}

	pi_ctx->sig_mr = ib_alloc_mr(pd, IB_MR_TYPE_SIGNATURE, 2);
	if (IS_ERR(pi_ctx->sig_mr)) {
		ret = PTR_ERR(pi_ctx->sig_mr);
		goto sig_mr_failure;
	}
	pi_ctx->sig_mr_valid = 0;
	desc->pi_ctx->sig_protected = 0;

	return 0;

sig_mr_failure:
	iser_free_reg_res(&pi_ctx->rsc);
alloc_reg_res_err:
	kfree(desc->pi_ctx);

	return ret;
}