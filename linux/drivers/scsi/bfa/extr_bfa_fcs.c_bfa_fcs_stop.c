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
struct bfa_fcs_s {int /*<<< orphan*/  wc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcs_exit_comp ; 
 int /*<<< orphan*/  bfa_fcs_fabric_modstop (struct bfa_fcs_s*) ; 
 int /*<<< orphan*/  bfa_wc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_fcs_s*) ; 
 int /*<<< orphan*/  bfa_wc_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_wc_wait (int /*<<< orphan*/ *) ; 

void
bfa_fcs_stop(struct bfa_fcs_s *fcs)
{
	bfa_wc_init(&fcs->wc, bfa_fcs_exit_comp, fcs);
	bfa_wc_up(&fcs->wc);
	bfa_fcs_fabric_modstop(fcs);
	bfa_wc_wait(&fcs->wc);
}