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
struct mv_cesa_ahash_dma_req {scalar_t__ padding; int /*<<< orphan*/  padding_dma; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {TYPE_1__* dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  padding_pool; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_2__* cesa_dev ; 
 scalar_t__ dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mv_cesa_ahash_dma_alloc_padding(struct mv_cesa_ahash_dma_req *req,
					   gfp_t flags)
{
	if (req->padding)
		return 0;

	req->padding = dma_pool_alloc(cesa_dev->dma->padding_pool, flags,
				      &req->padding_dma);
	if (!req->padding)
		return -ENOMEM;

	return 0;
}