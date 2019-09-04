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
struct request_queue {struct aoedev* queuedata; } ;
struct request {int dummy; } ;
struct aoedev {int flags; int /*<<< orphan*/  aoeminor; int /*<<< orphan*/  aoemajor; } ;

/* Variables and functions */
 int DEVFL_UP ; 
 int /*<<< orphan*/  aoe_end_request (struct aoedev*,struct request*,int) ; 
 int /*<<< orphan*/  aoecmd_work (struct aoedev*) ; 
 struct request* blk_peek_request (struct request_queue*) ; 
 int /*<<< orphan*/  blk_start_request (struct request*) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aoeblk_request(struct request_queue *q)
{
	struct aoedev *d;
	struct request *rq;

	d = q->queuedata;
	if ((d->flags & DEVFL_UP) == 0) {
		pr_info_ratelimited("aoe: device %ld.%d is not up\n",
			d->aoemajor, d->aoeminor);
		while ((rq = blk_peek_request(q))) {
			blk_start_request(rq);
			aoe_end_request(d, rq, 1);
		}
		return;
	}
	aoecmd_work(d);
}