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
struct scm_request {TYPE_2__* aob; struct request** request; } ;
struct request {int dummy; } ;
struct TYPE_3__ {size_t msb_count; } ;
struct TYPE_4__ {TYPE_1__ request; } ;

/* Variables and functions */

__attribute__((used)) static inline void scm_request_set(struct scm_request *scmrq,
				   struct request *req)
{
	scmrq->request[scmrq->aob->request.msb_count] = req;
}