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
struct scm_request {struct aob_rq_header* request; scalar_t__ aob; } ;
struct aob_rq_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct aob_rq_header*) ; 
 struct aob_rq_header* to_aobrq (struct scm_request*) ; 

__attribute__((used)) static void __scm_free_rq(struct scm_request *scmrq)
{
	struct aob_rq_header *aobrq = to_aobrq(scmrq);

	free_page((unsigned long) scmrq->aob);
	kfree(scmrq->request);
	kfree(aobrq);
}