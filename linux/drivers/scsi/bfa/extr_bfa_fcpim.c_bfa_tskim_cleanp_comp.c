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
struct bfa_tskim_s {int /*<<< orphan*/  itnim; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_TSKIM_SM_IOS_DONE ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_tskim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tm_io_comps ; 

__attribute__((used)) static void
bfa_tskim_cleanp_comp(void *tskim_cbarg)
{
	struct bfa_tskim_s *tskim = tskim_cbarg;

	bfa_stats(tskim->itnim, tm_io_comps);
	bfa_sm_send_event(tskim, BFA_TSKIM_SM_IOS_DONE);
}