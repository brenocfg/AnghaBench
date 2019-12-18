#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  ptr; } ;
struct ci_hw_ep {TYPE_1__ qh; scalar_t__ pending_td; } ;
struct ci_hdrc {int hw_ep_max; int /*<<< orphan*/  qh_pool; struct ci_hw_ep* ci_hw_ep; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_pending_td (struct ci_hw_ep*) ; 

__attribute__((used)) static void destroy_eps(struct ci_hdrc *ci)
{
	int i;

	for (i = 0; i < ci->hw_ep_max; i++) {
		struct ci_hw_ep *hwep = &ci->ci_hw_ep[i];

		if (hwep->pending_td)
			free_pending_td(hwep);
		dma_pool_free(ci->qh_pool, hwep->qh.ptr, hwep->qh.dma);
	}
}