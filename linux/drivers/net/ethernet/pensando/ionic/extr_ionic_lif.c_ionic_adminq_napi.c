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
struct napi_struct {int dummy; } ;
struct ionic_lif {TYPE_1__* notifyqcq; } ;
struct TYPE_4__ {struct ionic_lif* lif; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int IONIC_QCQ_F_INITED ; 
 int /*<<< orphan*/  ionic_adminq_service ; 
 int ionic_napi (struct napi_struct*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ionic_notifyq_clean (struct ionic_lif*,int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 TYPE_2__* napi_to_cq (struct napi_struct*) ; 

__attribute__((used)) static int ionic_adminq_napi(struct napi_struct *napi, int budget)
{
	struct ionic_lif *lif = napi_to_cq(napi)->lif;
	int n_work = 0;
	int a_work = 0;

	if (likely(lif->notifyqcq && lif->notifyqcq->flags & IONIC_QCQ_F_INITED))
		n_work = ionic_notifyq_clean(lif, budget);
	a_work = ionic_napi(napi, budget, ionic_adminq_service, NULL, NULL);

	return max(n_work, a_work);
}