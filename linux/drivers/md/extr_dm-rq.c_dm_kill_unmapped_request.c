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
struct request {int /*<<< orphan*/  rq_flags; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  RQF_FAILED ; 
 int /*<<< orphan*/  dm_complete_request (struct request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_kill_unmapped_request(struct request *rq, blk_status_t error)
{
	rq->rq_flags |= RQF_FAILED;
	dm_complete_request(rq, error);
}