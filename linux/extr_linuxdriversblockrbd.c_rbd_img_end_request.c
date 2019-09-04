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
struct rbd_img_request {scalar_t__ result; scalar_t__ xferred; int /*<<< orphan*/  rq; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_REQ_CHILD ; 
 int /*<<< orphan*/  blk_mq_end_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_rq_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno_to_blk_status (scalar_t__) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int /*<<< orphan*/  rbd_img_request_put (struct rbd_img_request*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbd_img_end_request(struct rbd_img_request *img_req)
{
	rbd_assert(!test_bit(IMG_REQ_CHILD, &img_req->flags));
	rbd_assert((!img_req->result &&
		    img_req->xferred == blk_rq_bytes(img_req->rq)) ||
		   (img_req->result < 0 && !img_req->xferred));

	blk_mq_end_request(img_req->rq,
			   errno_to_blk_status(img_req->result));
	rbd_img_request_put(img_req);
}