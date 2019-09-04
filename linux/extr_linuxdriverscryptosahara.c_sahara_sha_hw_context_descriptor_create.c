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
struct sahara_sha_reqctx {int /*<<< orphan*/  context_size; } ;
struct sahara_dev {TYPE_2__** hw_link; int /*<<< orphan*/  context_phys_base; TYPE_1__** hw_desc; int /*<<< orphan*/ * hw_phys_link; } ;
struct ahash_request {int dummy; } ;
struct TYPE_4__ {scalar_t__ next; int /*<<< orphan*/  p; int /*<<< orphan*/  len; } ;
struct TYPE_3__ {scalar_t__ p2; scalar_t__ len2; int /*<<< orphan*/  p1; int /*<<< orphan*/  len1; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  sahara_sha_init_hdr (struct sahara_dev*,struct sahara_sha_reqctx*) ; 

__attribute__((used)) static int sahara_sha_hw_context_descriptor_create(struct sahara_dev *dev,
						struct sahara_sha_reqctx *rctx,
						struct ahash_request *req,
						int index)
{
	dev->hw_desc[index]->hdr = sahara_sha_init_hdr(dev, rctx);

	dev->hw_desc[index]->len1 = rctx->context_size;
	dev->hw_desc[index]->p1 = dev->hw_phys_link[index];
	dev->hw_desc[index]->len2 = 0;
	dev->hw_desc[index]->p2 = 0;

	dev->hw_link[index]->len = rctx->context_size;
	dev->hw_link[index]->p = dev->context_phys_base;
	dev->hw_link[index]->next = 0;

	return 0;
}