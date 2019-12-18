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
struct esas2r_request {int /*<<< orphan*/ * data_buf; TYPE_2__* vrq; } ;
struct esas2r_adapter {int /*<<< orphan*/ ** req_table; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {TYPE_1__ scsi; } ;

/* Variables and functions */
 size_t LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_rq_free_sg_lists (struct esas2r_request*,struct esas2r_adapter*) ; 

__attribute__((used)) static inline void esas2r_rq_destroy_request(struct esas2r_request *rq,
					     struct esas2r_adapter *a)

{
	esas2r_rq_free_sg_lists(rq, a);
	a->req_table[LOWORD(rq->vrq->scsi.handle)] = NULL;
	rq->data_buf = NULL;
}