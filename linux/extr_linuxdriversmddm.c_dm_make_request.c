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
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  blk_qc_t ;

/* Variables and functions */
 int /*<<< orphan*/  __dm_make_request (struct request_queue*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __split_and_process_bio ; 

__attribute__((used)) static blk_qc_t dm_make_request(struct request_queue *q, struct bio *bio)
{
	return __dm_make_request(q, bio, __split_and_process_bio);
}