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
struct ionic_lif {int /*<<< orphan*/  deferred; int /*<<< orphan*/  state; } ;
struct ionic_deferred_work {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IONIC_DW_TYPE_LINK_STATUS ; 
 int /*<<< orphan*/  IONIC_LIF_LINK_CHECK_REQUESTED ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  ionic_lif_deferred_enqueue (int /*<<< orphan*/ *,struct ionic_deferred_work*) ; 
 int /*<<< orphan*/  ionic_link_status_check (struct ionic_lif*) ; 
 struct ionic_deferred_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ionic_link_status_check_request(struct ionic_lif *lif)
{
	struct ionic_deferred_work *work;

	/* we only need one request outstanding at a time */
	if (test_and_set_bit(IONIC_LIF_LINK_CHECK_REQUESTED, lif->state))
		return;

	if (in_interrupt()) {
		work = kzalloc(sizeof(*work), GFP_ATOMIC);
		if (!work)
			return;

		work->type = IONIC_DW_TYPE_LINK_STATUS;
		ionic_lif_deferred_enqueue(&lif->deferred, work);
	} else {
		ionic_link_status_check(lif);
	}
}