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
struct bfa_sfp_s {int /*<<< orphan*/  (* cbfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ lock; int /*<<< orphan*/  status; int /*<<< orphan*/  cbarg; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_trc (struct bfa_sfp_s*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_cb_sfp_show(struct bfa_sfp_s *sfp)
{
	bfa_trc(sfp, sfp->lock);
	if (sfp->cbfn)
		sfp->cbfn(sfp->cbarg, sfp->status);
	sfp->lock = 0;
	sfp->cbfn = NULL;
}