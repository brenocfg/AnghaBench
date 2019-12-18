#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct srp_request {scalar_t__ fr_list; } ;
struct srp_rdma_ch {TYPE_2__* target; } ;
struct TYPE_3__ {scalar_t__ end; scalar_t__ next; } ;
struct srp_map_state {struct scatterlist* sg; TYPE_1__ fr; } ;
struct scatterlist {int dummy; } ;
struct TYPE_4__ {scalar_t__ mr_per_cmd; } ;

/* Variables and functions */
 struct scatterlist* sg_next (struct scatterlist*) ; 
 int srp_map_finish_fr (struct srp_map_state*,struct srp_request*,struct srp_rdma_ch*,int,unsigned int*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int srp_map_sg_fr(struct srp_map_state *state, struct srp_rdma_ch *ch,
			 struct srp_request *req, struct scatterlist *scat,
			 int count)
{
	unsigned int sg_offset = 0;

	state->fr.next = req->fr_list;
	state->fr.end = req->fr_list + ch->target->mr_per_cmd;
	state->sg = scat;

	if (count == 0)
		return 0;

	while (count) {
		int i, n;

		n = srp_map_finish_fr(state, req, ch, count, &sg_offset);
		if (unlikely(n < 0))
			return n;

		count -= n;
		for (i = 0; i < n; i++)
			state->sg = sg_next(state->sg);
	}

	return 0;
}