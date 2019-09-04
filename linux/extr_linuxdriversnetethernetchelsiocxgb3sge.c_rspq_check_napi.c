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
struct sge_rspq {size_t cidx; int /*<<< orphan*/ * desc; } ;
struct sge_qset {int /*<<< orphan*/  napi; struct sge_rspq rspq; } ;

/* Variables and functions */
 scalar_t__ is_new_response (int /*<<< orphan*/ *,struct sge_rspq*) ; 
 int /*<<< orphan*/  napi_is_scheduled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rspq_check_napi(struct sge_qset *qs)
{
	struct sge_rspq *q = &qs->rspq;

	if (!napi_is_scheduled(&qs->napi) &&
	    is_new_response(&q->desc[q->cidx], q)) {
		napi_schedule(&qs->napi);
		return 1;
	}
	return 0;
}