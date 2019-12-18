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
struct bfa_tskim_s {int /*<<< orphan*/  itnim; int /*<<< orphan*/  notify; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFA_TSKIM_SM_CLEANUP ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_tskim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tm_cleanups ; 

void
bfa_tskim_cleanup(struct bfa_tskim_s *tskim)
{
	tskim->notify = BFA_TRUE;
	bfa_stats(tskim->itnim, tm_cleanups);
	bfa_sm_send_event(tskim, BFA_TSKIM_SM_CLEANUP);
}