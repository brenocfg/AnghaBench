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
struct nvme_tcp_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_SC_HOST_PATH_ERROR ; 
 int /*<<< orphan*/  blk_mq_rq_from_pdu (struct nvme_tcp_request*) ; 
 int /*<<< orphan*/  nvme_tcp_end_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvme_tcp_fail_request(struct nvme_tcp_request *req)
{
	nvme_tcp_end_request(blk_mq_rq_from_pdu(req), NVME_SC_HOST_PATH_ERROR);
}