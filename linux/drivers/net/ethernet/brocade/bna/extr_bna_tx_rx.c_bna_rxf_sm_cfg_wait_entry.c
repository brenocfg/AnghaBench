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
struct bna_rxf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_rxf_cfg_apply (struct bna_rxf*) ; 
 int /*<<< orphan*/  bna_rxf_sm_started ; 

__attribute__((used)) static void
bna_rxf_sm_cfg_wait_entry(struct bna_rxf *rxf)
{
	if (!bna_rxf_cfg_apply(rxf)) {
		/* No more pending config updates */
		bfa_fsm_set_state(rxf, bna_rxf_sm_started);
	}
}