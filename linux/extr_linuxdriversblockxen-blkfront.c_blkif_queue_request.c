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
struct request {int dummy; } ;
struct blkfront_ring_info {TYPE_1__* dev_info; } ;
struct TYPE_2__ {scalar_t__ connected; } ;

/* Variables and functions */
 scalar_t__ BLKIF_STATE_CONNECTED ; 
 scalar_t__ REQ_OP_DISCARD ; 
 scalar_t__ REQ_OP_SECURE_ERASE ; 
 int blkif_queue_discard_req (struct request*,struct blkfront_ring_info*) ; 
 int blkif_queue_rw_req (struct request*,struct blkfront_ring_info*) ; 
 scalar_t__ req_op (struct request*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int blkif_queue_request(struct request *req, struct blkfront_ring_info *rinfo)
{
	if (unlikely(rinfo->dev_info->connected != BLKIF_STATE_CONNECTED))
		return 1;

	if (unlikely(req_op(req) == REQ_OP_DISCARD ||
		     req_op(req) == REQ_OP_SECURE_ERASE))
		return blkif_queue_discard_req(req, rinfo);
	else
		return blkif_queue_rw_req(req, rinfo);
}