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
struct request_queue {int dummy; } ;
struct request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __elv_add_request (struct request_queue*,struct request*,int) ; 
 int /*<<< orphan*/  blk_account_io_start (struct request*,int) ; 

__attribute__((used)) static void add_acct_request(struct request_queue *q, struct request *rq,
			     int where)
{
	blk_account_io_start(rq, true);
	__elv_add_request(q, rq, where);
}