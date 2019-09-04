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
struct omap_aes_dev {int /*<<< orphan*/ * out_sg; int /*<<< orphan*/ * in_sg; int /*<<< orphan*/  flags; struct aead_request* aead_req; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int) ;} ;
struct aead_request {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_BUSY ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 

__attribute__((used)) static void omap_aes_gcm_finish_req(struct omap_aes_dev *dd, int ret)
{
	struct aead_request *req = dd->aead_req;

	dd->flags &= ~FLAGS_BUSY;
	dd->in_sg = NULL;
	dd->out_sg = NULL;

	req->base.complete(&req->base, ret);
}