#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spacc_req {int /*<<< orphan*/  result; TYPE_1__* req; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  dst_ddt; int /*<<< orphan*/  src_addr; int /*<<< orphan*/  src_ddt; } ;
struct ablkcipher_request {scalar_t__ src; scalar_t__ dst; int /*<<< orphan*/  nbytes; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct ablkcipher_request* ablkcipher_request_cast (TYPE_1__*) ; 
 int /*<<< orphan*/  spacc_free_ddt (struct spacc_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spacc_ablk_complete(struct spacc_req *req)
{
	struct ablkcipher_request *ablk_req = ablkcipher_request_cast(req->req);

	if (ablk_req->src != ablk_req->dst) {
		spacc_free_ddt(req, req->src_ddt, req->src_addr, ablk_req->src,
			       ablk_req->nbytes, DMA_TO_DEVICE);
		spacc_free_ddt(req, req->dst_ddt, req->dst_addr, ablk_req->dst,
			       ablk_req->nbytes, DMA_FROM_DEVICE);
	} else
		spacc_free_ddt(req, req->dst_ddt, req->dst_addr, ablk_req->dst,
			       ablk_req->nbytes, DMA_BIDIRECTIONAL);

	req->req->complete(req->req, req->result);
}