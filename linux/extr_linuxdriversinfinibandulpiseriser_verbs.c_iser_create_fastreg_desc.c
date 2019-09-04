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
struct iser_fr_desc {int /*<<< orphan*/  rsc; } ;
struct iser_device {int dummy; } ;
struct ib_pd {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct iser_fr_desc* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int iser_alloc_pi_ctx (struct iser_device*,struct ib_pd*,struct iser_fr_desc*,unsigned int) ; 
 int iser_alloc_reg_res (struct iser_device*,struct ib_pd*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  iser_free_reg_res (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iser_fr_desc*) ; 
 struct iser_fr_desc* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct iser_fr_desc *
iser_create_fastreg_desc(struct iser_device *device,
			 struct ib_pd *pd,
			 bool pi_enable,
			 unsigned int size)
{
	struct iser_fr_desc *desc;
	int ret;

	desc = kzalloc(sizeof(*desc), GFP_KERNEL);
	if (!desc)
		return ERR_PTR(-ENOMEM);

	ret = iser_alloc_reg_res(device, pd, &desc->rsc, size);
	if (ret)
		goto reg_res_alloc_failure;

	if (pi_enable) {
		ret = iser_alloc_pi_ctx(device, pd, desc, size);
		if (ret)
			goto pi_ctx_alloc_failure;
	}

	return desc;

pi_ctx_alloc_failure:
	iser_free_reg_res(&desc->rsc);
reg_res_alloc_failure:
	kfree(desc);

	return ERR_PTR(ret);
}