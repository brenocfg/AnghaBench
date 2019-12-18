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
struct bfa_ioim_s {int /*<<< orphan*/  dio; TYPE_1__* bfa; int /*<<< orphan*/  itnim; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  bfad; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOIM_SM_HCB ; 
 int /*<<< orphan*/  BFI_IOIM_STS_PATHTOV ; 
 int /*<<< orphan*/  bfa_cb_ioim_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_ioim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_tov_expired ; 

__attribute__((used)) static void
__bfa_cb_ioim_pathtov(void *cbarg, bfa_boolean_t complete)
{
	struct bfa_ioim_s *ioim = cbarg;

	bfa_stats(ioim->itnim, path_tov_expired);
	if (!complete) {
		bfa_sm_send_event(ioim, BFA_IOIM_SM_HCB);
		return;
	}

	bfa_cb_ioim_done(ioim->bfa->bfad, ioim->dio, BFI_IOIM_STS_PATHTOV,
			  0, 0, NULL, 0);
}