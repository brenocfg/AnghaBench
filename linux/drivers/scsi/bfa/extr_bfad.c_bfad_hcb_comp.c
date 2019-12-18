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
struct bfad_hal_comp {int /*<<< orphan*/  comp; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  bfa_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

void
bfad_hcb_comp(void *arg, bfa_status_t status)
{
	struct bfad_hal_comp *fcomp = (struct bfad_hal_comp *)arg;

	fcomp->status = status;
	complete(&fcomp->comp);
}