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
struct request {int dummy; } ;
struct blkif_req {int dummy; } ;

/* Variables and functions */
 struct blkif_req* blk_mq_rq_to_pdu (struct request*) ; 

__attribute__((used)) static inline struct blkif_req *blkif_req(struct request *rq)
{
	return blk_mq_rq_to_pdu(rq);
}