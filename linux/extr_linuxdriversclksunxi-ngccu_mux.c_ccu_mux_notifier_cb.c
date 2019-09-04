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
struct notifier_block {int dummy; } ;
struct ccu_mux_nb {int /*<<< orphan*/  delay_us; int /*<<< orphan*/  original_index; int /*<<< orphan*/  cm; int /*<<< orphan*/  common; int /*<<< orphan*/  bypass_index; } ;

/* Variables and functions */
 unsigned long POST_RATE_CHANGE ; 
 unsigned long PRE_RATE_CHANGE ; 
 int /*<<< orphan*/  ccu_mux_helper_get_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ccu_mux_helper_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int notifier_from_errno (int) ; 
 struct ccu_mux_nb* to_ccu_mux_nb (struct notifier_block*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccu_mux_notifier_cb(struct notifier_block *nb,
			       unsigned long event, void *data)
{
	struct ccu_mux_nb *mux = to_ccu_mux_nb(nb);
	int ret = 0;

	if (event == PRE_RATE_CHANGE) {
		mux->original_index = ccu_mux_helper_get_parent(mux->common,
								mux->cm);
		ret = ccu_mux_helper_set_parent(mux->common, mux->cm,
						mux->bypass_index);
	} else if (event == POST_RATE_CHANGE) {
		ret = ccu_mux_helper_set_parent(mux->common, mux->cm,
						mux->original_index);
	}

	udelay(mux->delay_us);

	return notifier_from_errno(ret);
}