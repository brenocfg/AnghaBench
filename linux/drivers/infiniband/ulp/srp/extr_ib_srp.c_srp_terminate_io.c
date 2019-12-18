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
struct srp_target_port {int ch_count; int req_ring_size; struct srp_rdma_ch* ch; } ;
struct srp_rport {struct srp_target_port* lld_data; } ;
struct srp_request {int dummy; } ;
struct srp_rdma_ch {struct srp_request* req_ring; } ;

/* Variables and functions */
 int DID_TRANSPORT_FAILFAST ; 
 int /*<<< orphan*/  srp_finish_req (struct srp_rdma_ch*,struct srp_request*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void srp_terminate_io(struct srp_rport *rport)
{
	struct srp_target_port *target = rport->lld_data;
	struct srp_rdma_ch *ch;
	int i, j;

	for (i = 0; i < target->ch_count; i++) {
		ch = &target->ch[i];

		for (j = 0; j < target->req_ring_size; ++j) {
			struct srp_request *req = &ch->req_ring[j];

			srp_finish_req(ch, req, NULL,
				       DID_TRANSPORT_FAILFAST << 16);
		}
	}
}