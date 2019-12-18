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
typedef  scalar_t__ u16 ;
struct request {int /*<<< orphan*/  rq_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_unique_tag (struct request*) ; 
 scalar_t__ blk_mq_unique_tag_to_hwq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 nvme_req_qid(struct request *req)
{
	if (!req->rq_disk)
		return 0;
	return blk_mq_unique_tag_to_hwq(blk_mq_unique_tag(req)) + 1;
}