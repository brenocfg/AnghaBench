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
struct sg_io_v4 {int /*<<< orphan*/  request_len; int /*<<< orphan*/  request; } ;
struct request {int dummy; } ;
struct bsg_job {int /*<<< orphan*/  request; int /*<<< orphan*/  request_len; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 struct bsg_job* blk_mq_rq_to_pdu (struct request*) ; 
 int /*<<< orphan*/  memdup_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uptr64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bsg_transport_fill_hdr(struct request *rq, struct sg_io_v4 *hdr,
		fmode_t mode)
{
	struct bsg_job *job = blk_mq_rq_to_pdu(rq);

	job->request_len = hdr->request_len;
	job->request = memdup_user(uptr64(hdr->request), hdr->request_len);

	return PTR_ERR_OR_ZERO(job->request);
}